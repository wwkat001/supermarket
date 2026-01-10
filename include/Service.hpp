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
#include"GoodsModel.hpp"

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
    void add(const TcpConnectionPtr&conn,json &js);
     void deleteUser(const TcpConnectionPtr&conn,json &js);
    //删Goods
     void deleteGoods(const TcpConnectionPtr&conn,json &js);
    //改M
     void updateGoodsNum(const TcpConnectionPtr&conn,json &js);
    //查
    void queryAllGoods(const TcpConnectionPtr&conn,json &js);
    //精准查询
    void querySingleGoods(const TcpConnectionPtr&conn,json &js);

    //商品销售(查询是否存在 存在 减数量)
    void saleGoods(const TcpConnectionPtr&conn,json &js);
    //进货
     void  purchaseGoods(const TcpConnectionPtr&conn,json &js);

    MsgHandler getHandler(int msg_id);

    private:

    ConnectionPool *_cp;

    Service();

    std::unordered_map<int,MsgHandler> _msgHandlerMap;

    UserModel _userModel;
    GoodsModel _goodsModel;
};

