#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<netinet/in.h>

int main()
{
	int listen_fd;
	int connect_fd;
	struct sockaddr_in listen_addr;
	struct sockaddr client_addr;
	char buffer[256];
	int ret;

	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_fd == -1)
	{
		printf("create listen socket error\n");
		return -1;
	}

	memset(&listen_addr, 0, sizeof(listen_addr));
	listen_addr.sin_family = AF_INET;
	listen_addr.sin_port = htons(8888);
	listen_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	ret = bind(listen_fd, &listen_addr, sizeof(listen_addr));
	if (ret == -1)
	{
		printf("bind addr error\n");
		return -1;
	}

	ret = listen(listen_fd, 128);
	if (ret == -1)
	{
		printf("listen fd error\n");
		return -1;
	}

	connect_fd = accept(listen_fd, NULL, NULL);
	if (connect_fd == -1)
	{
		printf("accept error\n");
		perror("accept error:");
		return -1;
	}

	do
	{
		memset(buffer, 0, 256);

		ret = recv(connect_fd, buffer, 255, 0);
		if (ret == -1)
		{
			printf("recv msg error\n");
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
		}
	}while(1);

	close(connect_fd);
	close(listen_fd);

	return 0;
}
