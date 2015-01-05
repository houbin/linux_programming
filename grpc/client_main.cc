#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include "util/logger.h"
#include "util/errcode.h"
#include "src/discovery.h"                                                                                                                
#include "src/vms_client.h"

using namespace client;
using namespace util;

int main()
{
    //char storage_server_ip[32] = "192.168.6.12";
    Logger *logger = NULL;

    NewLogger("/tmp/client.log", &logger);

    struct sockaddr_in in_addr;
    struct sockaddr_in out_addr;

#define DISCOVERY_RECV_PORT 9002
#define DISCOVERY_SEND_PORT 9001
    out_addr.sin_family = AF_INET;
    out_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    out_addr.sin_port = htons(DISCOVERY_SEND_PORT);
    in_addr.sin_family = AF_INET;
    in_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    in_addr.sin_port = htons(DISCOVERY_RECV_PORT);

    Discovery discovery(logger, in_addr, out_addr, 10000);

#define VMSCLIENT_SEND_PORT 9003
    struct in_addr out_buffer;
    out_addr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.6.12", &out_buffer);
    out_addr.sin_addr.s_addr = out_buffer.s_addr;
    out_addr.sin_port = htons(VMSCLIENT_SEND_PORT);
    memset(&in_addr, 0, sizeof(struct sockaddr_in));
    VMS_CLIENT vms_client(logger, in_addr, out_addr, 5000);
    
    discovery.Bind();
    vms_client.Bind();

    discovery.Start();
    vms_client.Start();

    discovery.Join();
    vms_client.Join();

    return 0;
}
