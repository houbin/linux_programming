#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include "udp_client.h"
#include "../grpc/grpc.h"
#include "../grpc/storage_json.h"

namespace client
{

UDP_CLIENT::UDP_CLIENT(Logger *logger, struct sockaddr_in &recv_addr, struct sockaddr_in &send_addr, int timeout_milliseconds)
: if_use_recv_addr_to_send_(false), if_broadcast_(false), timeout_milliseconds_(timeout_milliseconds)
{
    logger_ = logger;
    memcpy(&recv_addr_, &recv_addr, sizeof(recv_addr_));
    memcpy(&send_addr_, &send_addr, sizeof(send_addr_));

    if (send_addr_.sin_addr.s_addr == htonl(INADDR_BROADCAST))
    {
        if_broadcast_ = true;
    }
}

int32_t UDP_CLIENT::Bind()
{
    int optval = 1;
    int32_t ret = 0;;

    Log(logger_, "bind");

    fd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd_ < 0)
    {
        Log(logger_, "create socket error: %s", strerror(errno));
        return -errno;
    }

    ret = setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    if (ret < 0)
    {
        Log(logger_, "setsockopt reuseaddr error: %s", strerror(errno));
        return -errno;
    }

    if (if_broadcast_)
    {
        ret = setsockopt(fd_, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval));
        if (ret < 0)
        {
            Log(logger_, "setsockopt broadcast error: %s", strerror(errno));
            return -errno;
        }
    }

    ret = bind(fd_, (struct sockaddr *)&recv_addr_, sizeof(struct sockaddr_in));
    if (ret < 0)
    {
        Log(logger_, "bind error: %s", strerror(errno));
        return -errno;
    }

    return 0;
}

int32_t UDP_CLIENT::Start()
{
    Log(logger_, "start");

    Create();

    return 0;
}


void *UDP_CLIENT::Entry()
{
    int ret;
    grpcInitParam_t init_param;
    UserDefInfo user_info;

    user_info.fd = this->fd_;
    user_info.logger = this->logger_;
    memcpy(&(user_info.send_addr), &(this->send_addr_), sizeof(user_info.send_addr));
    memcpy(&(user_info.recv_addr), &(this->recv_addr_), sizeof(user_info.recv_addr));
    user_info.if_use_recv_addr_to_send = false;
    user_info.parent = (void *)this;

    memset(&init_param, 0, sizeof(init_param));
    init_param.userdef = &user_info;
    init_param.fptr_net.recv = RecvUdp;
    init_param.fptr_net.send = SendUdp;
    init_param.methodList = storage_json_methodList;

    grpc_t *grpc = grpc_new();
    grpc_init(grpc, &init_param);
    grpc->timeout_milliseconds = timeout_milliseconds_;

    while(true)
    {
        PrepareSendRequest(grpc);
        ret = SendRequest(grpc);
        PostSendRequest(grpc, ret);

        grpc_end(grpc);
    }

    grpc_delete(grpc);
    if (fd_ > 0)
    {
        close(fd_);
        fd_ = -1;
    }

    Log(logger_, "entry end");
    return 0;
}

void UDP_CLIENT::Stop()
{
    done_ = true;

    Log(logger_, "stop");

    if (fd_ > 0)
    {
        ::close(fd_);
        fd_ = -1;
    }

    if (IsStarted())
    {
        Join();
    }

    done_ = false;
}

}

