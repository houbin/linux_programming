#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int seq = 0;

void handler(int arg)
{
    seq ++;
    printf("helle, signal, seq %d\n", seq);

    return;
}

int main()
{
    struct sigaction oldact;
    struct sigaction act;
    memset(&act, 0, sizeof(act));

    act.sa_handler = handler;
    sigfillset(&act.sa_mask);
    act.sa_flags = SA_RESETHAND;

    if (sigaction(SIGUSR1, &act, NULL) == -1)
    {
        printf("sigaction error, exit now\n");
        return -1;
    }

    printf("pid is %ld\n", getpid());

    while(true)
    {
        printf("sleep, seq %d\n", seq);
        sleep(2);
    }

    return 0;
}
