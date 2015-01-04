#ifndef CLIENT_DISCOVERY_H_
#define CLIENT_DISCOVERY_H_

#include <stdbool.h>
#include <netinet/in.h>
#include "../util/logger.h"
#include "../util/thread.h"
#include "../grpc/storage_json.h"
#include "udp_client.h"

using namespace util;

#define CLIENT_SEND_PORT 9001¬
#define CLIENT_RECV_PORT 9002¬

namespace client
{

class Discovery : public UDP_CLIENT
{
private:
    Logger *logger_;
    PARAM_REQ_storage_json_broadcast_discovery req_;
    PARAM_RESP_storage_json_broadcast_discovery resp_;

public:
    Discovery(Logger *logger, struct sockaddr_in &in_addr, struct sockaddr_in &out_addr, int timeout_milliseconds)
    : UDP_CLIENT(logger, in_addr, out_addr, timeout_milliseconds), logger_(logger) { }

    int32_t PrepareSendRequest(grpc_t *grpc);
    int32_t SendRequest(grpc_t *grpc);
    int32_t PostSendRequest(grpc_t *grpc, int ret);
};

}
#endif

