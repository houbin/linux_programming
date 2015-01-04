#ifndef STORAGE_UDP_CLIENT_H_
#define STORAGE_UDP_CLIENT_H_

#include <stdbool.h>
#include <netinet/in.h>
#include "../util/thread.h"
#include "../util/logger.h"
#include "grpc_userdef.h"

using namespace util;

namespace client
{

class UDP_CLIENT : public Thread
{
private:
    int fd_;
    Logger *logger_;
    struct sockaddr_in recv_addr_;
    struct sockaddr_in send_addr_;
    bool if_use_recv_addr_to_send_;
    bool if_broadcast_;
    int timeout_milliseconds_;
    bool done_;

public:
    UDP_CLIENT(Logger *logger, struct sockaddr_in &recv_addr, struct sockaddr_in &send_addr, int timeout_milliseconds = -1);

    int32_t Bind();
    int32_t Start();
    void *Entry();
    void Stop();

    virtual int32_t PrepareSendRequest(grpc_t *grpc) = 0;
    virtual int32_t SendRequest(grpc_t *grpc) = 0;
    virtual int32_t PostSendRequest(grpc_t *grpc, int ret) = 0;
};

}
#endif
