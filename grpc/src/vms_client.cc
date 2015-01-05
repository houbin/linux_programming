#include "vms_client.h"
#include <unistd.h>

namespace client
{

VMS_CLIENT::VMS_CLIENT(Logger *logger, struct sockaddr_in &in_addr, struct sockaddr_in &out_addr, int timeout_milliseconds)
: UDP_CLIENT(logger, in_addr, out_addr, timeout_milliseconds), logger_(logger)
{

}

int32_t VMS_CLIENT::PrepareSendRequest(grpc_t *grpc)
{
    UserDefInfo *user_info = (UserDefInfo *)grpc->userdef;
    
    Log(logger_, "PrepareSendRequest start");

    req_.channels_cnt = 1;
    req_.channels = (channels_t*)grpc_malloc(grpc, req_.channels_cnt * sizeof(channels_t));
    Log(user_info->logger, "malloc size is %d", req_.channels_cnt * sizeof(channels_t));
    
    for (int i = 0; i < req_.channels_cnt; i++)
    {
        req_.channels[i].type = grpc_strdup(grpc, "ipc");
        req_.channels[i].sid = grpc_strdup(grpc, "abcdefg");
        req_.channels[i].protocol = grpc_strdup(grpc, "cloudsee");
        req_.channels[i].bMainStream = true;
        req_.channels[i].bSubStream = false;
        req_.channels[i].mainstream = grpc_strdup(grpc, "rstp://127.0.0.1/live0.264");
        req_.channels[i].substream = grpc_strdup(grpc, "rstp://127.0.0.1/live1.264");
        req_.channels[i].ip = grpc_strdup(grpc, "127.0.0.1");
        req_.channels[i].port = grpc_strdup(grpc, "9101");
        req_.channels[i].channelcnt = 1;
        req_.channels[i].channelid = 0;
        req_.channels[i].name = grpc_strdup(grpc, "admin");
        req_.channels[i].passwd = grpc_strdup(grpc, "123456");
        req_.channels[i].streamserverip = grpc_strdup(grpc, "192.168.6.107");
        req_.channels[i].streamserverport = 9005;
    }

    return 0;
}

int32_t VMS_CLIENT::SendRequest(grpc_t *grpc)
{
    Log(logger_, "SendRequest");
    return CLIENT_storage_json_channel_add(grpc, &req_, &resp_);
}

int32_t VMS_CLIENT::PostSendRequest(grpc_t *grpc, int ret)
{
    Log(logger_, "PostSendRequest");
    sleep(10);
    return 0;
}

}
