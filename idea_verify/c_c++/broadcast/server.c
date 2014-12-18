#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define LISTEN_PORT 8888
#define SEND_PORT 12345

int udp_recv(int sockfd, struct sockaddr_in *send_addr, int len)
{
    int ret = 0;
    int seq = 0;
    char buffer[1024];
    struct sockaddr_in src_addr;

    while(1)
    {
        memset(buffer, 0, 1024);

        socklen_t length = sizeof(src_addr);
        ret = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&src_addr, &length);
        if (ret < 0)
        {
            perror("[udp_recv] recvfrom error");
            return -1;
        }

        printf("server: recv msg %s\n", buffer);
        seq = atoi(buffer);
        printf("server: send back msg %d\n", seq+1);

        memset(buffer, 0, 1024);
        snprintf(buffer, 1024, "%d", seq+1);

        ret = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)send_addr, (socklen_t)len);
        if (ret < 0)
        {
            perror("[udp_recv] sendto error");
            return -1;
        }
        printf("server: send back msg %d ok\n\n", seq+1);
    }

    return 0;
}


int main()
{
	int ret;
	int listen_fd;
	uint32_t yes = 1;
	struct sockaddr_in send_addr;
	struct sockaddr_in listen_addr;

	listen_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (listen_fd == -1)
	{
		perror("create socket error");
		return -1;
	}

    ret = setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    if (ret < 0)
    {
        perror("setsockopt reuseaddr error");
        return -1;
    }

	ret = setsockopt(listen_fd, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes));
	if (ret < 0)
	{
		perror("setsockopt so_broadcast error\n");
		return -1;
	}

	memset(&listen_addr, 0, sizeof(listen_addr));
	listen_addr.sin_family = AF_INET;
	listen_addr.sin_port = htons(LISTEN_PORT);
	listen_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	ret = bind(listen_fd, (struct sockaddr *)&listen_addr, sizeof(listen_addr));
	if (ret == -1)
	{
		perror("bind addr error");
		return -1;
	}

    memset(&send_addr, 0, sizeof(send_addr));
    send_addr.sin_family = AF_INET;
    send_addr.sin_port = htons(SEND_PORT);
	send_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);

    udp_recv(listen_fd, &send_addr, sizeof(send_addr));

	close(listen_fd);

	return 0;
}
