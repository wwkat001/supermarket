#pragma once

#include<TcpConnection.h>
#include<unordered_map>
#include<functional>
#include<memory>

#include"json.hpp"

using json=nlohmann::json;

using MsgHandler=std::function<void(const std::shared_ptr<TcpConnection> &conn,json &js)>;

class Service
{
    public:
    static Service *instance();

    void defaultHandler(const std::shared_ptr<TcpConnection>&conn,json &js);
    //添加其他服务，参数与defaultHandler一致


    MsgHandler getHandler(int msg_id);

    private:

    Service();

    std::unordered_map<int,MsgHandler> _msgHandlerMap;
};

