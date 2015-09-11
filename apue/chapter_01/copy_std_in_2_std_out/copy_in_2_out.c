#include "../apue.h"

int main(int argc, char *argv[])
{
    int n;
    char buffer[1024] = {0};

    while ((n = read(STDIN_FILENO, buffer, 1023)) > 0)
    {
        int temp = 0;
        if ( (temp = write(STDOUT_FILENO, buffer, strlen(buffer))) != n)
        {
            perror("write error");
            return -1;
        }
    }

    if (n < 0)
    {
        perror("read error");
        return -1;
    }

    return 0;
}
