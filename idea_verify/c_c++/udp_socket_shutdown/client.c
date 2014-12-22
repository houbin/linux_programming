#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define MAXLINE 4096
#define MULTICAST_ADDR "225.0.0.37"
#define MULTICAST_PORT 12345

int main(int argc, char** argv)
{
    int    sockfd, n;
    char    recvline[4096], sendline[4096];
    struct sockaddr_in servaddr;
	struct sockaddr_in src_addr;

    if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
    printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
    exit(0);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MULTICAST_PORT);
	servaddr.sin_addr.s_addr = inet_addr(MULTICAST_ADDR);
	
	while(1)
	{
	    printf("send msg to server: \n");
	    fgets(sendline, 4096, stdin);
	    if( sendto(sockfd, sendline, strlen(sendline), 0 ,(struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	    {
		   printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
	 	   exit(0);
		}

		char buffer[256] = {0};
		int addr_len = sizeof(struct sockaddr_in);
		if (recvfrom(sockfd, buffer, 256, 0, &src_addr, &addr_len) < 0)
		{
		   printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
	 	   exit(0);
		}

		printf("recvfrom server: %s\n\n", buffer);
	}


    close(sockfd);
    exit(0);
}
