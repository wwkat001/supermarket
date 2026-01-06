#pragma once

#include<TcpConnection.h>
#include<unordered_map>
#include<functional>
#include<memory>

#include<ConnectionPool.h>
#include"Connection.h"
#include"json.hpp"
#include"UserModel.hpp"
#include"Log.hpp"

using json=nlohmann::json;

using MsgHandler=std::function<void(const TcpConnectionPtr &conn,json &js)>;

class Service
{
    public:
    static Service *instance();

    void defaultHandler(const TcpConnectionPtr &conn,json &js);
    //添加其他服务，参数与defaultHandler一致

    //注册
    void regist(const TcpConnectionPtr&conn,json &js);

    //查询所有用户
    void queryAllUser(const TcpConnectionPtr&conn,json &js);
    
    //登陆
    void login(const TcpConnectionPtr&conn,json &js);
    //增M

    //删M

    //改M

    //查

    //精准查询

    //用户管理 M

    //商品销售

    //进货

    MsgHandler getHandler(int msg_id);

    private:

    ConnectionPool *_cp;

    Service();

    std::unordered_map<int,MsgHandler> _msgHandlerMap;

    UserModel _userModel;
};

