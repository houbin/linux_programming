#include "../apue.h"
#

int main()
{
    pid_t pid;
    char buffer[128] = {0};
    int status = 0;

    printf("%% ");
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
