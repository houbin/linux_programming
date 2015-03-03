#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<netinet/in.h>

#define MULTICAST_ADDR "225.0.0.37"
#define MULTICAST_PORT 8888

int main()
{
	int listen_fd;
	struct sockaddr_in listen_addr;
	struct sockaddr client_addr;
	char buffer[256];
	int ret;
	uint32_t yes = 1;
	struct ip_mreq mreq;

	listen_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (listen_fd == -1)
	{
		printf("create listen socket error\n");
		return -1;
	}

	ret = setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
	if (ret < 0)
	{
		printf("setsockopt error\n");
		return ret;
	}

	memset(&listen_addr, 0, sizeof(listen_addr));
	listen_addr.sin_family = AF_INET;
	listen_addr.sin_port = htons(12345);
	listen_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	ret = bind(listen_fd, &listen_addr, sizeof(listen_addr));
	if (ret == -1)
	{
		printf("bind addr error\n");
		return -1;
	}

	mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_ADDR);
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);
	ret = setsockopt(listen_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
	if (ret < 0)
	{
		perror("setsockopt");
		return ret;
	}
	
	do
	{
		memset(buffer, 0, 256);
		int addr_len = sizeof(struct sockaddr_in);

		struct sockaddr_in src_addr;
		ret = recvfrom(listen_fd, buffer, 255, 0, &src_addr, &addr_len);
		if (ret == -1)
		{
			perror("recv msg error");
			return -1;
		}
		
		if (ret == 0)
		{
			printf("peer socket have been shutdown\n");
			break;
		}
		else
		{
			printf("%s\n", buffer);
			ret = sendto(listen_fd, buffer, strlen(buffer), 0, &src_addr, sizeof(struct sockaddr));
			if (ret < 0)
			{
				perror("sendto error");
				return -1;
			}
		}
	}while(1);

	close(listen_fd);

	return 0;
}
