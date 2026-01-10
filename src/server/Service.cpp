#include "Service.hpp"

#include <string>
#include <vector>
#include <unordered_map>

Service::Service() : _cp(ConnectionPool::getConnectionPool())
{
    // 注册服务
    _msgHandlerMap.emplace(1,std::bind(&Service::regist,std::placeholders::_1,std::placeholders::_2));
    _msgHandlerMap.emplace(1,std::bind(&Service::queryAllUser,std::placeholders::_1,std::placeholders::_2));
    _msgHandlerMap.emplace(1,std::bind(&Service::login,std::placeholders::_1,std::placeholders::_2));
    _msgHandlerMap.emplace(1,std::bind(&Service::add,std::placeholders::_1,std::placeholders::_2));
    _msgHandlerMap.emplace(1,std::bind(&Service::deleteUser,std::placeholders::_1,std::placeholders::_2));
    _msgHandlerMap.emplace(1,std::bind(&Service::deleteGoods,std::placeholders::_1,std::placeholders::_2));
    _msgHandlerMap.emplace(1,std::bind(&Service::updateGoodsNum,std::placeholders::_1,std::placeholders::_2));
    _msgHandlerMap.emplace(1,std::bind(&Service::queryAllGoods,std::placeholders::_1,std::placeholders::_2));
    _msgHandlerMap.emplace(1,std::bind(&Service::querySingleGoods,std::placeholders::_1,std::placeholders::_2));
    _msgHandlerMap.emplace(1,std::bind(&Service::saleGoods,std::placeholders::_1,std::placeholders::_2));
    _msgHandlerMap.emplace(1,std::bind(&Service::purchaseGoods,std::placeholders::_1,std::placeholders::_2));
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
        response["success"] = 1;
        response["error_msg"] = " ";

        conn->send(response.dump());
    }
    else
    {
        log("user_id:", user_id, "register failed");
        json response;
        response["msg_id"] = 11;
        response["success"] = 0;
        response["error_msg"] = " ";

        conn->send(response.dump());
    }
}

void Service::queryAllUser(const TcpConnectionPtr &conn, json &js)
{
    std::shared_ptr<Connection> sp = _cp->getConnection();

    std::vector<User> user_info;
    user_info = _userModel.allFieldsResToVector(sp->query(_userModel.query_all()));

    json response;
    response["msg_id"] = 21;
    response["users_info"] = _userModel.allFieldsUserToStringInVector(user_info);

    conn->send(response.dump());
}

void Service::login(const TcpConnectionPtr &conn, json &js)
{

    std::shared_ptr<Connection> sp = _cp->getConnection();

    int user_id = js["user_id"].get<int>();
    std::string password = js["password"];

    std::vector<User> res = _userModel.allFieldsResToVector(sp->query(_userModel.query_for_login(user_id, password)));

    json response;

    if (res.size() == 1)
    {
        log("login success");
        if (res[0].getIsManager() == 1)
        {
            response["msg_id"] = 31;
            response["is_manager"] = 1;
            response["success"] = 1;
        }
        else
        {
            response["msg_id"] = 31;
            response["is_manager"] = 0;
            response["success"] = 1;
        }
    }
    else
    {
        response["msg_id"] = 31;
        response["is_manager"] = 0;
        response["success"] = 0;
        log("login failed");
    }

    conn->send(response.dump());
}

void Service::add(const TcpConnectionPtr &conn, json &js)
{
    std::string goods_name = js["goods_name"];
    int num = js["num"].get<int>();

    std::shared_ptr<Connection> sp = _cp->getConnection();

    json response;
    if (sp->update(_goodsModel.insert(goods_name, num)))
    {
        response["msg_id"] = 41;
        response["success"] = 1;
    }
    else
    {
        response["msg_id"] = 41;
        response["success"] = 0;
    }
    conn->send(response.dump());
}

void Service::deleteUser(const TcpConnectionPtr &conn, json &js)
{

    int user_id = js["user_id"].get<int>();
    std::shared_ptr<Connection> sp = _cp->getConnection();

    json response;
    if (sp->update(_userModel.deleteByUserId(user_id)))
    {
        response["msg_id"] = 51;
        response["success"] = 1;
    }
    else
    {
        response["msg_id"] = 51;
        response["success"] = 0;
    }
    conn->send(response.dump());
}

void Service::deleteGoods(const TcpConnectionPtr &conn, json &js)
{

    std::string goods_name = js["goods_name"];

    std::shared_ptr<Connection> sp = _cp->getConnection();
    json response;
    if (sp->update(_goodsModel.deleteGoodsByName(goods_name)))
    {
        response["msg_id"] = 61;
        response["success"] = 1;
    }
    else
    {
        response["msg_id"] = 61;
        response["success"] = 0;
    }
    conn->send(response.dump());
}

void Service::updateGoodsNum(const TcpConnectionPtr &conn, json &js)
{
    int goods_num = js["goods_num"].get<int>();

    std::string goods_name = js["goods_name"];
    std::shared_ptr<Connection> sp = _cp->getConnection();
    json response;
    if (sp->update(_goodsModel.updateGoodsNumByName(goods_name, goods_num)))
    {
        response["msg_id"] = 71;
        response["success"] = 1;
    }
    else
    {
        response["msg_id"] = 71;
        response["success"] = 0;
    }
    conn->send(response.dump());
}

void Service::queryAllGoods(const TcpConnectionPtr &conn, json &js)
{
    std::shared_ptr<Connection> sp = _cp->getConnection();
    sp->query(_goodsModel.queryAllGoods());
    std::vector<Goods> goods_info;
    goods_info = _goodsModel.allFieldsResToVector(sp->query(_goodsModel.queryAllGoods()));
    json response;
    response["msg_id"] = 81;
    response["goods_info"] = _goodsModel.allFieldsGoodsToStringInVector(goods_info);
    conn->send(response.dump());
}

void Service::querySingleGoods(const TcpConnectionPtr &conn, json &js)
{
    std::string goods_name = js["goods_name"];
    std::shared_ptr<Connection> sp = _cp->getConnection();

    std::vector<Goods> goods_info;
    goods_info = _goodsModel.allFieldsResToVector(sp->query(_goodsModel.queryByName(goods_name)));
    json response;
    if (goods_info.empty())
    {

        response["success"] = 0;
    }
    else
    {
        response["msg_id"] = 91;
        response["success"] = 1;
        response["goods_info"] = _goodsModel.allFieldsGoodsToStringInVector(goods_info);
    }

    conn->send(response.dump());
}

void Service::saleGoods(const TcpConnectionPtr &conn, json &js)
{
    int goods_num = js["goods_num"].get<int>();
    std::string goods_name = js["goods_name"];
    std::shared_ptr<Connection> sp = _cp->getConnection();

    json response;
    std::vector<Goods> goods_info;
    goods_info = _goodsModel.allFieldsResToVector(sp->query(_goodsModel.queryByName(goods_name)));

    if (goods_info.empty())
    {
        response["msg_id"] = 91;
        response["success"] = 0;
        response["goods_info"] = " ";
        response["error_msg"]="no such goods";
        
    }
    else
    {
        int num = goods_info[0].getNum();

        if (num >= goods_num)
        {
            num=num-goods_num;
            sp->update(_goodsModel.updateGoodsNumByName(goods_name,num));
             goods_info[0].setNum(num);
               response["msg_id"] = 101;
        response["success"] = 1;
        response["goods_info"] = _goodsModel.allFieldsGoodsToStringInVector(goods_info);
        response["error_msg"]=" ";
          
        }
        else{
        response["msg_id"] = 101;
        response["success"] = 0;
        response["goods_info"] = " ";   
        response["error_msg"]="not enough";
        
        }
      
    }

    conn->send(response.dump());
}

void Service::purchaseGoods(const TcpConnectionPtr &conn, json &js)
{  
     int goods_num = js["goods_num"].get<int>();
    std::string goods_name = js["goods_name"];
    std::shared_ptr<Connection> sp = _cp->getConnection();
  
      json response;
    if((sp->update(_goodsModel.insert(goods_name,goods_num)))){
         
        response["msg_id"] = 121;
        response["success"] = 1;

    }
    else{
        response["msg_id"] = 121;
        response["success"] = 0;

    }
      conn->send(response.dump());

}
