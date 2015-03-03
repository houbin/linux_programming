#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

using namespace std;

int main()
{
    int fd;

    fd = open("./test.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("open fd error");
        return -1;
    }

    char buffer[1024];
    memset(buffer, 0, 1024);

    while (true)
    {
        int ret = read(fd, buffer, 1024);
        if (ret < 0)
        {
            perror("ret error");
            return -1;
        }

        printf("ret is %d, buffer is %s\n", ret, buffer);
        sleep(20);
    }

    return 0;
}
