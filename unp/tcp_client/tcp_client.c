#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
//#include "unp.h"

int main(int argc, char *argv[])
{
    int ret;
    int fd;
    struct sockaddr_in server_addr;

    if (argc < 2)
    {
        printf("args too short\n");
        return -1;
    }

    while (true)
    {
        fd = socket(AF_INET, SOCK_STREAM, 0);
        if (fd < 0)
        {
            printf("create socket error, errno is %s\n", strerror(errno));
            return -1;
        }

        struct in_addr temp;
        ret = inet_pton(AF_INET, argv[1], &temp);
        if (ret != 1)
        {
            printf("inet_pton error\n");
            return -1;
        }
        
        memset(&server_addr, 0, sizeof(struct sockaddr_in));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = temp.s_addr;
        server_addr.sin_port = htons(8004);
        ret = connect(fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
        if (ret < 0)
        {
            printf("connect error, errno is %s\n", strerror(errno));
            return -1;
        }

        char buffer[] = "get date time";

        ret = send(fd, buffer, sizeof(buffer), 0);
        if (ret < 0)
        {
            printf("send error, errno is %s\n", strerror(errno));
            return -1;
        }

        char str_temp[1024];
        memset(str_temp, 0, 1024);

        int n = 0;
        while((n = read(fd, str_temp, 1024)) > 0)
        {
            str_temp[n] = 0;
            if (fputs(str_temp, stdout) == EOF)
            {
                perror("fputs error");
            }
        }

        if (n < 0)
        {
            perror("read error");
        }

        close(fd);
        sleep(2);
    }

    return 0;
}
