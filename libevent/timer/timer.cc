#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <event2/event.h>
#include <event2/event_struct.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/queue.h>

struct event_base *base = NULL;
struct event *ev = NULL;
struct timeval tv;

void timer_cb(evutil_socket_t fd, short event, void *arg)
{
    printf("timer timeout, fd is %d, event is %d\n", fd, event);

    event_add(ev, &tv);

    return;
}

int main()
{
    base = event_base_new();
    ev = evtimer_new(base, &timer_cb, base);

    tv.tv_sec = 2;
    tv.tv_usec = 0;
    event_add(ev, &tv);

    event_base_dispatch(base);

    return 0;
}
