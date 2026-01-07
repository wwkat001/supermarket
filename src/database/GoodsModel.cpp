#include "GoodsModel.hpp"

char *GoodsModel::insert(const std::string &_name, int _num)
{
    char sql[200]={0};
    snprintf(sql,200,"insert into products(name,num) values('%s',%d)",_name,_num);
    return sql;
}