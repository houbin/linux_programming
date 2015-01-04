#ifndef CLIENT_STREAM_SERVICE_H_
#define CLIENT_STREAM_SERVICE_H_

#include "../grpc/storage_json.h"
#include "udp_service.h"

namespace client
{

class StreamService : public UDP_SERVICE
{
public:
    StreamService(Logger *logger, struct sockaddr_in &in_addr, struct sockaddr_in &out_addr);
    : UDP_SERVICE(logger, in_addr, out_addr) { }
};

}

#endif
