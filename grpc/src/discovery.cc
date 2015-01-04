#include "discovery.h"
#include "unistd.h"

namespace client
{

int32_t Discovery::PrepareSendRequest(grpc_t *grpc)
{
    /* req don't need to anything */

    return 0;
}

int32_t Discovery::SendRequest(grpc_t *grpc)
{
    return CLIENT_storage_json_broadcast_discovery(grpc, &req_, &resp_);
}

int32_t Discovery::PostSendRequest(grpc_t *grpc, int ret)
{
    if (ret < 0)
    {
        return 0;
    }

    /* print devices that was discovered */
    Log(logger_, "find device, type is %s, sid is %s, ip is %s, port is %s, channelcnt is %d", resp_.type,
        resp_.sid, resp_.ip, resp_.port, resp_.channelcnt);
    sleep(10);

    return 0;
}

}
