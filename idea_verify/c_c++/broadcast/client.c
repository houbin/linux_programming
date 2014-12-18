#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE 4096
#define SEND_PORT 8888
#define LISTEN_PORT 12345

int udp_send(int sockfd, struct sockaddr_in *send_addr, int len)
{
    int ret = 0;
    int count = 0;
    char buffer[1024] ;

    while(count < 100)
    {
        memset(buffer, 0, 1024);
        snprintf(buffer, 1024, "%d", count);
        printf("we will send msg %d\n", count);
        printf("we want to recv msg %d\n", count+1);

        ret = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)send_addr, len);
        if (ret == -1)
        {
            perror("[udp_send] sendto error");
            return -1;
        }

        memset(buffer, 0, 1024);
        struct sockaddr_in recv_addr;
        int length = sizeof(recv_addr);
        ret = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&recv_addr, (socklen_t *)&length);
        if (ret < 0)
        {
            perror("[udp_send] recvfrom error");
            return -1;
        }

        char temp[1024] = {0};
        const char *ptemp = inet_ntop(AF_INET, (void *)&(recv_addr.sin_addr), temp, 1024);
        printf("we1 have recv %s from %s:%d\n\n", buffer, ptemp, recv_addr.sin_port);
		count ++;
   }

    return 0;
}

int main(int argc, char** argv)
{
	int ret;
    int sockfd;
	int optval = 1;
    struct sockaddr_in send_addr;
    struct sockaddr_in listen_addr;

    if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
        exit(0);
    }

    ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    if (ret < 0)
    {
        perror("setsockopt reuseaddr error");
        return -1;
    }

	ret = setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval));
	if (ret < 0)
	{
		perror("setsockopt error");
		return -1;
	}

    memset(&listen_addr, 0, sizeof(listen_addr));
    listen_addr.sin_family = AF_INET;
    listen_addr.sin_port = htons(LISTEN_PORT);
	listen_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    ret = bind(sockfd, (struct sockaddr *)&listen_addr, sizeof(listen_addr));
    if (ret < 0)
    {
        perror("bind error");
        return -1;
    }

    memset(&send_addr, 0, sizeof(send_addr));
    send_addr.sin_family = AF_INET;
    send_addr.sin_port = htons(SEND_PORT);
	send_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);

    udp_send(sockfd, &send_addr, sizeof(send_addr));
	
    close(sockfd);
    exit(0);
}
