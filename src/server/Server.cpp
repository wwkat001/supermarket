#include"server.hpp"
#include"TcpConnection.h"

#include"log.hpp"

#include<string>
#include<functional>

Server::Server(EventLoop *loop_,const char*ip_,const int port_)
:_server(loop_,ip_,port_),
_loop(loop_)
{
    _server.set_connection_callback(std::bind(&Server::onConnection,this,std::placeholders::_1));
    _server.set_message_callback(std::bind(&Server::onMessage,this,std::placeholders::_1));

    _server.SetThreadNums(16);
}

void Server::start()
{
    
}

void Server::onConnection(const std::shared_ptr<TcpConnection>&conn)
{
    if(conn->state()==conn->Connected)
    {
        log()
    }
}

void Server::onMessage(const std::shared_ptr<TcpConnection> &conn)
{
    
}
