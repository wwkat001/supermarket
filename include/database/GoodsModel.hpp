#pragma once

#include"Goods.hpp"
#include"Model.hpp"

class GoodsModel :public Model
{
    public:

    std::string insert(const std::string &_name,int _num);

    std::string deleteGoodsByName(std::string &_name);

    std::string updateGoodsNumByName(std::string &_name,int _num);

    std::string queryAllGoods();

    std::string queryByName(std::string &_name);
   

    std::vector<Goods> allFieldsResToVector(MYSQL_RES *res);

    std::vector<std::string> allFieldsGoodsToStringInVector(std::vector<Goods> goods_info);

};