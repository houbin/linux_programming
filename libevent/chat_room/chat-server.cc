#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <event2/event.h>
#include <event2/event_struct.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/queue.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <error.h>
#include <deque>
#include "mutex.h"
#include "cond.h"

#define LISTEN_PORT 9000

using namespace std;
using namespace util;

extern void on_accept(int fd, short ev, void *arg);
extern void buffered_on_read(struct bufferevent *bev, void *arg);
extern void buffered_on_error(struct bufferevent *bev, short what, void *arg);

int setnonblock(int fd)
{
    int flags = 0;

    flags = fcntl(fd, F_GETFL);
    if (flags < 0)
    {
        return flags;
    }

    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) < 0)
    {
        return -1;
    }

    return 0;
}

typedef struct client
{
    int fd;
    struct bufferevent *buf_ev;
}Client;

class ClientQueue
{
private:
    Mutex mutex_;
    Cond cond_;
    deque<Client*> queue_;

public:
    ClientQueue() : mutex_("ClientQueue")
    {
        
    }

    ~ClientQueue()
    {
    
    }

    void Put(Client *client)
    {
        Mutex::Locker lock(mutex_);
        queue_.push_back(client);
        cond_.Signal();
    }

    void Get(Client *client)
    {
        Mutex::Locker lock(mutex_);

        while(queue_.empty())
        {
            cond_.Wait(&mutex_);
        }

        client = queue_.front();
        queue_.pop_front();
    }

    void Remove(Client *remove_client)
    {
        Mutex::Locker lock(mutex_);

        deque<Client*>::iterator iter = queue_.begin();
        for(iter; iter != queue_.end(); iter++)
        {
            Client *client = *iter;
            if (client == remove_client)
            {
                queue_.erase(iter);
                break;
            }
        }
    }

    void SendData(uint8_t *buffer, size_t n, Client *exclude_client)
    {
        Mutex::Locker lock(mutex_);

        deque<Client*>::iterator iter = queue_.begin();
        for (iter; iter != queue_.end(); iter++)
        {
            Client *client = *iter;
            if (client == exclude_client)
            {
                continue;
            }

            bufferevent_write(client->buf_ev, buffer, n);
        }
    }
};

int tcp_server_init(int port)
{
    int ret = 0;
    int listen_fd = 0;
    int reuseaddr_on = 1;
    struct sockaddr_in listen_addr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0)
    {
        perror("create socket error");
        return -1;
    }

    memset(&listen_addr, 0, sizeof(listen_addr));
    listen_addr.sin_family = AF_INET;
    listen_addr.sin_addr.s_addr = INADDR_ANY;
    listen_addr.sin_port = htons(port);

    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_on, sizeof(reuseaddr_on));

    ret = bind(listen_fd, (struct sockaddr*)&listen_addr, sizeof(listen_addr));
    if (ret < 0)
    {
        perror("bind error");
        return -1;
    }

    ret = listen(listen_fd, SOMAXCONN);
    if (ret < 0)
    {
        perror("listen error");
        return -1;
    }

    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_on, sizeof(reuseaddr_on));
    ret = setnonblock(listen_fd);
    if (ret < 0)
    {
        return -1;
    }

    return listen_fd;
}

struct event_base *evbase = NULL;
ClientQueue client_queue;

int main()
{
    int ret = 0;
    int listen_fd;
    struct event ev_accept;

    listen_fd = tcp_server_init(LISTEN_PORT);
    if (listen_fd < 0)
    {
        printf("tcp server init error\n");
        return -1;
    }

    printf("tcp server init ok, listen fd %d\n", listen_fd);

    evbase = event_base_new();
    event_assign(&ev_accept, evbase, listen_fd, EV_READ|EV_PERSIST, on_accept, NULL);
    event_add(&ev_accept, NULL);

    event_base_dispatch(evbase);
    event_base_free(evbase);

    return 0;
}

void on_accept(int fd, short ev, void *arg)
{
    int ret = 0;
    int client_fd;
    Client *client = NULL;
    struct sockaddr_in client_addr;

    printf("on_accept, fd %d, ev %d\n", fd, ev);

    socklen_t client_len = sizeof(client_addr);

    client_fd = accept(fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0)
    {
        perror("accept error");
        return;
    }

    printf("accept ok, client address is %s, port is %d\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);

    ret = setnonblock(client_fd);
    if (ret < 0)
    {
        return;
    }

    client = (Client *)malloc(sizeof(Client));
    if (client == NULL)
    {
        return;
    }

    client->fd = client_fd;
    client->buf_ev = bufferevent_socket_new(evbase, client_fd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(client->buf_ev, buffered_on_read, NULL, buffered_on_error, client);
    bufferevent_enable(client->buf_ev, EV_READ);

    client_queue.Put(client);

    return;
}

void buffered_on_read(struct bufferevent *bev, void *arg)
{
    int ret = 0;
    Client *this_client = (Client*)arg;
    Client *client = NULL;
    uint8_t buffer[8192];
    size_t n;

    for(;;)
    {
        n = bufferevent_read(bev, buffer, sizeof(buffer));
        if (n <= 0)
        {
            break;
        }

        printf("recv msg: %s, and send to other client\n", buffer);

        client_queue.SendData(buffer, n, this_client);
    }

    return;
}

void buffered_on_error(struct bufferevent *bev, short what, void *arg)
{
    Client *client = (Client *)arg;

    if (what & BEV_EVENT_EOF)
    {
        printf("Client disconnect\n");
    }
    else
    {
        printf("Client socket error, disconnecting\n");
    }

    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);

    memset(&client_addr, 0, len);

    int ret = getsockname(client->fd, (struct sockaddr*)&client_addr, &len);
    if (ret != 0)
    {
        printf("getsockname error\n");
    }
    else
    {
        printf("remove client: ip %s, port %d\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
    }

    client_queue.Remove(client);
    bufferevent_free(client->buf_ev);
    close(client->fd);
    free(client);
    return;
}

