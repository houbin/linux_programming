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
#include <errno.h>
#include <deque>
#include "mutex.h"
#include "cond.h"

#define LISTEN_PORT 9000

using namespace std;
using namespace util;

extern void cmd_msg_cb(int fd, short events, void *arg);
extern void event_cb(struct bufferevent *bev, short event, void *arg);
extern void server_msg_cb(struct bufferevent *bev, void *ctx);

int tcp_connect_server(const char *server_ip, int port)
{
    int ret;
    int sockfd;
    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));

    ret = inet_aton(server_ip, &addr.sin_addr);

    printf("server ip %s, port %d\n", server_ip, port);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("create socket error");
        return -errno;
    }

    ret = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret != 0)
    {
        perror("connect error");
        return -1;
    }

    evutil_make_socket_nonblocking(sockfd);

    return sockfd;
}

int main(int argc, char *argv[])
{
    int ret = 0;
    int fd;

    char server_ip[] = "127.0.0.1";
    int port = LISTEN_PORT;

    fd = tcp_connect_server(server_ip, port);
    if (ret < 0)
    {
        printf("connect server error\n");
        return -1;
    }

    printf("connect server successful\n");

    struct event_base *base = event_base_new();
    struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);

    struct event *cmd_event = event_new(base, STDIN_FILENO, EV_READ|EV_PERSIST, cmd_msg_cb, (void *)bev);
    event_add(cmd_event, NULL);

    bufferevent_setcb(bev, server_msg_cb, NULL, event_cb, cmd_event);
    bufferevent_enable(bev, EV_READ|EV_WRITE|EV_PERSIST);

    event_base_dispatch(base);

    printf("finished\n");

    return 0;
}

void cmd_msg_cb(int fd, short events, void *arg)
{
    char msg[1024] = {0};

    int ret = read(fd, msg, sizeof(msg));
    if (ret < 0)
    {
        printf("read msg error\n");
        return;
    }

    struct bufferevent *bev = (struct bufferevent *)arg;
    bufferevent_write(bev, msg, ret);

    printf("send msg %s\n", msg);

    return;
}

void server_msg_cb(struct bufferevent *bev, void *ctx)
{
    char msg[1024] = {0};

    size_t len = bufferevent_read(bev, msg, sizeof(msg));
    msg[len] = '\0';

    printf("recv msg: %s\n", msg);

    return;
}

void event_cb(struct bufferevent *bev, short event, void *arg)
{
    if (event & BEV_EVENT_EOF)
    {
        printf("connection closed\n");
    }
    else if (event & BEV_EVENT_ERROR)
    {
        printf("some other error\n");
    }

    bufferevent_free(bev);

    struct event *ev = (struct event *)arg;

    event_free(ev);

    return;
}


