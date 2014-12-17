#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define MAXLINE 4096
#define SEND_PORT 12345

int main(int argc, char** argv)
{
	int ret;
	int optval = 1;
    int  sockfd, n;
    char recvline[4096];
	char sendline[4096] = "abcdefg";
    struct sockaddr_in servaddr;
	struct sockaddr_in src_addr;

    if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
    printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
    exit(0);
    }

	ret = setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval));
	if (ret < 0)
	{
		perror("setsockopt error");
		return -1;
	}

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SEND_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	
	int i = 0;
	for (i = 0; i < 100; i++)
	{
	    printf("send msg to server: %s\n", sendline);
	    if( sendto(sockfd, sendline, strlen(sendline), 0 ,(struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	    {
		   printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
	 	   exit(0);
		}
	}


    close(sockfd);
    exit(0);
}
