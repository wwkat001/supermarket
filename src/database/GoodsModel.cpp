#include "GoodsModel.hpp"

char *GoodsModel::insert(const std::string &_name, int _num)
{
    char sql[200]={0};
    snprintf(sql,200,"insert into products(name,num) values('%s',%d)",_name,_num);
    return sql;
}

char *GoodsModel::deleteGoodsByName(std::string &_name)
{     
    char sql[200]={0};
    snprintf(sql,200,"delete from products where name='%s'",_name);    
    return sql;
}



char *GoodsModel::updateGoodsNumByName(std::string &_name, int _num)
{
    char sql[200]={0};
    snprintf(sql,200,"update products set num=%d where name='%s'",_num,_name);
    return sql;
}

char *GoodsModel::queryAllGoods()
{
    char sql[200]={"select * from products"};
    return sql;
}
