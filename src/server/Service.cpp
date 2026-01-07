#include "Service.hpp"

#include <string>
#include <vector>
#include <unordered_map>

Service::Service() : _cp(ConnectionPool::getConnectionPool())
{
    // 注册服务
}

Service *Service::instance()
{
    static Service service;
    return &service;
}

void Service::defaultHandler(const TcpConnectionPtr &conn, json &js)
{
    return;
}

void Service::regist(const TcpConnectionPtr &conn, json &js)
{
    std::shared_ptr<Connection> sp = _cp->getConnection();
    int user_id = js["user_id"].get<int>();
    std::string userName = js["user_name"];
    std::string password = js["password"];
    bool is_manager = js["is_manager"].get<bool>();
    if (sp->update(_userModel.insert(user_id, userName, password, is_manager)))
    {
        log("user_id:", user_id, "register success");

        // 发送返回消息
    }
    else
    {
        log("user_id:", user_id, "register failed");
    }
}

void Service::queryAllUser(const TcpConnectionPtr &conn, json &js)
{
    
}

void Service::login(const TcpConnectionPtr &conn, json &js)
{
    std::shared_ptr<Connection> sp = _cp->getConnection();
    int user_id = js["user_id"].get<int>();
    std::string password = js["password"];

    if(sp->query(_userModel.query_for_login(user_id,password)))
    {
        log("login success");
    }
    else
    {
        log("login failed");
    }
}

MsgHandler Service::getHandler(int msg_id)
{
    auto it = _msgHandlerMap.find(msg_id);
    if (it == _msgHandlerMap.end())
    {
        return std::bind(&Service::defaultHandler, this, std::placeholders::_1, std::placeholders::_2);
    }
    else
    {
        return _msgHandlerMap[msg_id];
    }
}
void Service::add(const TcpConnectionPtr &conn, json &js)
{
    std::string goods_name=js["goods_name"];
    int num=js["num"].get<int>();

    std::shared_ptr<Connection> sp=_cp->getConnection();

    sp->update(_goodsModel.insert(goods_name,num));
}
