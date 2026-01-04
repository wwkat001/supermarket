#include"Service.hpp"

#include<string>
#include<vector>
#include<unordered_map>

Service::Service()
{
    //注册服务

}

Service *Service::instance()
{
    static Service service;
    return &service;
}

void Service::defaultHandler(const std::shared_ptr<TcpConnection>&conn,json &js)
{
    return;
}

MsgHandler Service::getHandler(int msg_id)
{
    auto it=_msgHandlerMap.find(msg_id);
    if(it==_msgHandlerMap.end())
    {
        return std::bind(&Service::defaultHandler,this,std::placeholders::_1,std::placeholders::_2);
    }
    else
    {
        return _msgHandlerMap[msg_id];
    }
}


