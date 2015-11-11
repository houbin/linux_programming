#include <stdio.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

struct bufferevent *bev = NULL;
struct event_base *base = NULL;

void *func(void *arg)
{
    if (bev != NULL)
    {
        char msg[32] = "hello world";
        bufferevent_write(bev, msg, strlen(msg));

        printf("thread: bufferevent_write hello world\n");
    }

    return NULL;
}

void read_cb(struct bufferevent *bev, void *arg)
{
    int ret = 0;
    char buffer[32] = {0};

    ret = bufferevent_read(bev, buffer, 32);

    printf("bufferevent read %s\n", buffer);
    struct timeval tv = {2, 0};
//    event_base_loopexit(base, &tv);
    sleep(2);
    printf("read over, so free bev\n");
    bufferevent_free(bev);
}

void error_cb(struct bufferevent *bev, short event, void *arg)
{
    if (event &BEV_EVENT_EOF)
    {
        printf("socket closed\n");
    }
    else if (event & BEV_EVENT_ERROR)
    {
        printf("socket error\n");
    }
    else if (event & BEV_EVENT_CONNECTED)
    {
        printf("socket connected\n");
    }

    return ;
}


int main()
{
    base = event_base_new();
    bev = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);
    
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(8004);

    bufferevent_socket_connect(bev, (struct sockaddr*)&addr, sizeof(addr));
    bufferevent_setcb(bev, read_cb, NULL, error_cb, NULL);
    bufferevent_enable(bev, EV_READ|EV_PERSIST);

    pthread_t t;
    pthread_create(&t, NULL, func, NULL);

    event_base_dispatch(base);
    
    return 0;
}

