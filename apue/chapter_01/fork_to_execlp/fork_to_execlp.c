#include "../apue.h"
#include <signal.h>

void signal_handle(int sig_num)
{
    printf("signal sig number %d\n", sig_num);

    return ;
}

int main()
{
    pid_t pid;
    char buffer[128] = {0};
    int status = 0;
    struct sigaction new;
    memset(&new, 0, sizeof(struct sigaction));

    new.sa_handler = signal_handle;

    if (sigaction(SIGINT, &new, NULL) != 0)
    {
        printf("sigaction error\n");
        return -1;
    }

    while(fgets(buffer, 127, stdin) != NULL)
    {
        int length = strlen(buffer);
        if (buffer[length - 1] == '\n')
            buffer[length - 1] = 0;

        pid = fork();
        if (pid < 0)
        {
            perror("fork error");
            return -1;
        }
        else if (pid == 0)
        {
            // child
            execlp(buffer, buffer, (char *)0);
            printf("could not execute %s\n", buffer);
            exit(127);
        }

        //parent
        if ((pid = waitpid(pid, &status, 0)) < 0)
        {
            perror("waitpid error");
            return -1;
        }
        printf("waitpid return %d\n", pid);
        printf("%% ");
    }

    exit(0);
}
