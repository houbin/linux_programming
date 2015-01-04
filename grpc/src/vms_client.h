#ifndef CLIENT_VMS_CLIENT_H_
#define CLIENT_VMS_CLIENT_H_

#include "../util/logger.h"
#include "../grpc/storage_json.h"
#include "../grpc/grpc.h"
#include "udp_client.h"

namespace client
{

class VMS_CLIENT : public UDP_CLIENT
{
private:
    Logger *logger_;
    PARAM_REQ_storage_json_channel_add req_;
    PARAM_RESP_storage_json_channel_add resp_;

public:
    VMS_CLIENT(Logger *logger, struct sockaddr_in &in_addr, struct sockaddr_in &out_addr, int timeout_milliseconds);

    int32_t PrepareSendRequest(grpc_t *grpc);
    int32_t SendRequest(grpc_t *grpc);
    int32_t PostSendRequest(grpc_t *grpc, int ret);
};

}

#endif
