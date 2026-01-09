#pragma once

#include"Goods.hpp"
#include"Model.hpp"

class GoodsModel :public Model
{
    public:

    char* insert(const std::string &_name,int _num);

    char *deleteGoodsByName(std::string &_name);

    char *updateGoodsNumByName(std::string &_name,int _num);

    char *queryAllGoods();

    std::vector<Goods> allFieldsResToVector(MYSQL_RES *res);

    std::vector<std::string> allFieldsGoodsToStringInVector(std::vector<Goods> goods_info);

};