#pragma once

#include"Goods.hpp"

#include<string>

class GoodsModel
{
    public:

    char* insert(const std::string &_name,int _num);

    char *deleteGoodsByName(std::string &_name);

    char *updateGoodsNumByName(std::string &_name,int _num);

    char *queryAllGoods();
};