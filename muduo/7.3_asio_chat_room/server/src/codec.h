#ifndef CODEC_H_
#define CODEC_H_

#include <boost/noncopyable.hpp>
#include <boost/function.hpp>

#include <muduo/base/Timestamp.h>
#include <muduo/net/Buffer.h>
#include "../util/logger.h"

class LengthHeaderCodec : public boost::noncopyable
{
public:
    boost::function<void (const muduo::net::TcpConnectionPtr&,
                          const muduo::string &message, 
                          const muduo::Timestamp) > StringMessageCallback;
    explicit LengthHeaderCodec(const StringMessageCallback &cb)
    : message_callback_(cb)
    {}
    
    void OnMessage(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer *buf, muduo::Timestamp receive_time)
    {
        while (buf->readableBytes() >= kHeaderLen)
        {
            char *data = buf->peek();
            int32_t be32 = *static_cast<const int32_t*>(data);
            const int32_t len = muduo::net::sockets::networkToHost32(be32);

            if (len < 0 || len > 65535)
            {
                LOG_DEBUG(g_logger, "invalid length %d", len);
                conn->shutdown();
                break;
            }
            else if (len + kHeaderLen <= buf->readableBytes())
            {
                buf->retrieve(kHeaderLen);
                muduo::string message(buf->peek(), len);
                message_callback_(conn, message, receive_time);
                buf->retrieve(len);
            }
            else
            {
                break;
            }
        }
    }

    void Send(muduo::net::TcpConnectionPtr *conn, const muduo::StringPiece &message)
    {
        muduo::net::Buffer buf;
        buf.append(message.data(), message.size());
        int32_t len = static_cast<int32_t>(message.size());
        int32_t be32 = muduo::net::sockets::hostToNetwork32(len);
        buf.prepend(&be32, sizeof be32);
        conn->send(&buf);
    }

private:
    StringMessageCallback message_callback_;
    const static size_t kHeaderLen = sizeof(int32_t);
};

#endif

