#pragma once

#include<TcpServer.h>
#include<EventLoop.h>

#include"Service.hpp"

class Server
{
    public:

    Server(EventLoop *loop_,const InetAddress &listenAddr_,const std::string &nameArg_);

    void start();

    private:

    void onConnection(const TcpConnectionPtr&conn);

    void onMessage(const TcpConnectionPtr &conn,Buffer*buffer,Timestamp time);

    TcpServer _server;
    EventLoop *_loop;
    
};