#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <time.h>

int main()
{
    int ret;
    int server_fd;
    struct sockaddr_in server_addr;
    time_t n;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        perror("create socket error");
        return -1;
    }

    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(8004);
    
    int sock_opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (void *)&sock_opt, sizeof(sock_opt)))
    {
        return -1;
    }

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
    listen(server_fd, 128);

    while (true)
    {
        struct sockaddr_in recv_addr = {0};
        int connect_fd = accept(server_fd, (struct sockaddr*)NULL, NULL);
        if (connect_fd == -1)
        {
            perror("accept error");
            return -1;
        }

        char buffer[64] = {0};
        ret = read(connect_fd, buffer, 64);
        printf("read msg is %s, ret is %d\n", buffer, ret);

        n = time(NULL);

        char write_buffer[64] = {0};
        sprintf(write_buffer, "%s", ctime(&n));
        ret = write(connect_fd, write_buffer, strlen(write_buffer));
        if (ret == -1)
        {
            perror("write error");
        }

        close(connect_fd);
    }

    return 0;
}
