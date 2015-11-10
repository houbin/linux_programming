#include "../include/unp.h"
#include "time.h"
#include "string.h"
#include "stdint.h"
#include "stdbool.h"

int main()
{
    int fd;
    int ret;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("create socket error");
        return -1;
    }

    struct sockaddr_in in_addr;
    memset((void*)&in_addr, 0, sizeof(struct sockaddr_in));

    in_addr.sin_family = AF_INET;
    in_addr.sin_addr.s_addr = INADDR_ANY;
    in_addr.sin_port = htons(13);
    
    ret = bind(fd, (struct sockaddr *)&in_addr, sizeof(struct sockaddr_in));
    if (ret < 0)
    {
        perror("bind error");
        return -1;
    }

    ret = listen(fd, 128);
    if (ret < 0)
    {
        perror("listen error");
        return -1;
    }

    while (true)
    {
        int accept_fd;
        accept_fd = accept(fd, NULL, 0);
        if (accept_fd < 0)
        {
            perror("accept error");
            return -1;
        }

        char buffer[1024] = {0};
        ret = read(accept_fd, buffer, 1023);
        if (ret < 0)
        {
            perror("read error");
            continue;
        }

        printf("accept buffer is %s/n", buffer);

        time_t ticks;
        ticks = time(NULL);
        char *time_str = ctime(&ticks);
        memset(buffer, 0, 1024);
        ret = snprintf(buffer, 1023, "time is %s", time_str);

        ret = write(accept_fd, buffer, strlen(buffer));
        if (ret < 0)
        {
            perror("write error");
        }
    }

    return 0;
}
