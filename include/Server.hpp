#pragma once

#include<TcpServer.h>
#include<EventLoop.h>

class Server
{
    public:

    Server(EventLoop *loop_,const char*ip_,const int port_);

    void start();

    private:

    void onConnection(const std::shared_ptr<TcpConnection>&conn);

    void onMessage(const std::shared_ptr<TcpConnection> &conn);

    TcpServer _server;
    EventLoop *_loop;
};