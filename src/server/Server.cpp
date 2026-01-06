#include"Server.hpp"
#include"TcpConnection.h"
#include"Buffer.h"
#include"Log.hpp"
#include"json.hpp"

#include<string>
#include<functional>

using json=nlohmann::json;

Server::Server(EventLoop *loop_,const InetAddress &listenAddr_,const std::string &nameArg_)
:_server(loop_,listenAddr_,nameArg_),
_loop(loop_)
{
    _server.setConnectionCallback(std::bind(&Server::onConnection,this,std::placeholders::_1));
    _server.setMessageCallback(std::bind(&Server::onMessage,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));

    _server.setThreadNum(16);
}

void Server::start()
{
    
}

void Server::onConnection(const TcpConnectionPtr&conn)
{
    if(conn->connected())
    {
        log();
    }
}

void Server::onMessage(const TcpConnectionPtr &conn,Buffer*buffer,Timestamp time)
{
    std::string buf=buffer->retrieveAllAsString();
    log("receive:",buf);

    json js=json::parse(buf);
}
