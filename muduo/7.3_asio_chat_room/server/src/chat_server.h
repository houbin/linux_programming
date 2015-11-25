#ifndef CHAT_SERVER_H_
#define CHAT_SERVER_H_

#include <boost/noncopyable.hpp>
#include "../include/muduo/net/EventLoop.h"
#include "../include/muduo/net/InetAddress.h"
#include "../include/muduo/net/TcpConnection.h"

using namespace muduo;
using namespace muduo::net;

class ChatServer : boost::nocopyable
{
public:
    ChatServer(EventLoop *loop, const InetAddress &listen_addr)
    : loop_(loop), server_(loop, listen_addr, "ChatServer"), codec_(boost::bind(&ChatServer::onStringMessage, this, _1, _2, _3))
    {
        server_.setConnectionCallback(boost::bind(&ChatServer::onConnection, this, _1));
        server_.setMessageCallback(boost::bind(&ChatServer::onMessage, &codec_, _1, _2, _3));
    }

    ~ChatServer()
    {}

    void Start()
    {
        server_.start();
    }

private:
    typedef std::set<TcpConnection> ConnectionList;

    EventLoop loop_;
    TcpServer server_;
    LengthHeaderCodec codec_;
    ConnectionList connections_;
};

#endif

