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
        json response;
        response["msg_id"] = 11;
        response["success"] =1;
        response["error_msg"]=" ";

        conn->send(response.dump());
    }
    else
    {
        log("user_id:", user_id, "register failed");
        json response;
        response["msg_id"] = 11;
        response["success"] =0;
        response["error_msg"]=" ";

        conn->send(response.dump());
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

    std::vector<User> res=_userModel.allFieldsResToVector(sp->query(_userModel.query_for_login(user_id, password)));
    if (res.size()==1)
    {
        log("login success");
    }
    else
    {
        log("login failed");
    }
}

void Service::add(const TcpConnectionPtr &conn, json &js)
{
    std::string goods_name = js["goods_name"];
    int num = js["num"].get<int>();

    std::shared_ptr<Connection> sp = _cp->getConnection();

    sp->update(_goodsModel.insert(goods_name, num));
}
