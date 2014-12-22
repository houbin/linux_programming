#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <poll.h>
#include "grpc/grpc.h"
#include "grpc/storage_json.h"

typedef struct{
    int fd;
    struct sockaddr_in send_addr;
}UserDefInfo;

int recv_test(grpc_t *grpc, void *buffer, int len, int *timeout)
{
	int ret = 0;
	struct pollfd pfd;
	UserDefInfo *user_info = (UserDefInfo *)grpc->userdef;
	int fd = user_info->fd;
	
	pfd.fd = user_info->fd;
	pfd.events = POLLIN | POLLERR | POLLNVAL | POLLHUP;
	ret = poll(&pfd, 1, -1);
	if (ret < 0)
	{
        perror("poll error");
		return -errno;
	}

	if (pfd.revents & (POLLERR | POLLNVAL | POLLHUP));
	{
        printf("events is POLLERR\n");
		return -1;
	}

	ret = recvfrom(fd, buffer, len, 0, NULL, NULL);
	if (ret < 0)
	{
		return -errno;
	}

	return 0;
}

int send_test(grpc_t *grpc, void *buffer, int len)
{
    int fd;
	int ret = 0;
	UserDefInfo *user_info = (UserDefInfo *)grpc->userdef;

	assert(user_info != NULL);
	assert(user_info->fd > 0);

	fd = user_info->fd;

	ret = sendto(fd, buffer, len, 0, (struct sockaddr *)&(user_info->send_addr), sizeof(struct sockaddr_in));
	if (ret < 0)
	{
		return -errno;
	}

	return 0;
}


#define CLIENT_SEND_PORT 9001
#define CLIENT_RECV_PORT 9002

int32_t client_bind(int *fd)
{
	int ret;
	int optval = 1;
    int client_fd;
	struct sockaddr_in client_addr;

	client_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (client_fd < 0)
	{
        perror("create socket error");
		return -1;
	}

	ret = setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	if (ret < 0)
	{
        perror("setsockopt reuseaddr error");
		return -1;
	}

	ret = setsockopt(client_fd, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval));
	if (ret < 0)
	{
        perror("setsockopt broadcast error");
		return -1;
	}

	memset(&client_addr, 0, sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	client_addr.sin_port = htons(CLIENT_RECV_PORT);

	ret = bind(client_fd, (struct sockaddr *)&client_addr, sizeof(client_addr));
	if (ret < 0)
	{
        perror("bind error");
		return -1;
	}

    *fd = client_fd;
	return 0;
}

int main(int argc, char *argv[])
{
    int ret = 0;
    int client_fd = 0;
    grpcInitParam_t init_param;
    UserDefInfo user_info = {0};

    ret = client_bind(&client_fd);
    if (ret < 0)
    {
        printf("client_bind error\n");
        return ret;
    }

    user_info.fd = client_fd;
    user_info.send_addr.sin_family = AF_INET;
    user_info.send_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    user_info.send_addr.sin_port = htons(CLIENT_SEND_PORT);

    memset(&init_param, 0, sizeof(init_param));
    init_param.userdef = &user_info;
    init_param.fptr_net.recv = recv_test;
    init_param.fptr_net.send = send_test;
    init_param.methodList = storage_json_methodList;

    while(1)
    {
        grpc_t *grpc = grpc_new();
        grpc_init(grpc, &init_param);

        while(1)
        {
            PARAM_RESP_storage_json_broadcast_discovery resp;
            ret = CLIENT_storage_json_broadcast_discovery(grpc, &users, &resp);
            if (ret  == 0)
            {
                printf("\ndiscovery get one\n");
                printf("type: %s\n", resp.type);
                printf("sid: %s\n", resp.sid);
                printf("ip: %s\n", resp.ip);
                printf("mac: %s\n", resp.mac);
            }
            else
            {
                printf("error happened: %d, %s\n", grpc->error.errcode, grpc->error.message);
            }
            grpc_end(grpc);
            sleep(2);
        }

        grpc_delete(grpc);
    }


    return 0;
}
