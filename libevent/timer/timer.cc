#include <iostream>
#include <event2/event.h>
#include <event.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>

int count = 0;

struct Args
{
    struct event *ev;
    struct timeval tv;
};

void timeout_cb(int fd, short event, void *params)
{
    Args *arg = (Args*)params;
    struct event *ev = arg->ev;
    struct timeval tv = arg->tv;

    printf("timeout\n");
    evtimer_del(ev);
}

int main()
{
    struct event_base *base = event_base_new();
    struct event *timeout = NULL;
    struct timeval tv = {2, 0};

    Args *arg = new Args();
    timeout = evtimer_new(base, timeout_cb, arg);
    arg->ev = timeout;
    arg->tv = tv;
    evtimer_add(timeout, &tv);
    event_base_dispatch(base);

    sleep(100);

    return 0;
}


