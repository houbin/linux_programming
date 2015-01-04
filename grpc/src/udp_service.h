#ifndef STORAGE_UDP_SERVICE_H_
#define STORAGE_UDP_SERVICE_H_

#include <stdbool.h>
#include <netinet/in.h>
#include "../util/thread.h"
#include "../util/logger.h"
#include "grpc_userdef.h"

using namespace util;
namespace client
{

class UDP_SERVICE : public Thread
{
private:
    int fd_;
    Logger *logger_;
    struct sockaddr_in recv_addr_;
    struct sockaddr_in send_addr_;
    bool if_use_recv_addr_to_send_;
    bool if_broadcast_;
    int recv_timeout_milliseconds_;
    bool done_;

public:
    UDP_SERVICE(Logger *logger, struct sockaddr_in &recv_addr, struct sockaddr_in &send_addr, int recv_timeout_milliseconds = -1);

    int32_t Bind();
    int32_t Start();
    void *Entry();
    void Stop();
};

}

#endif

