#include "GoodsModel.hpp"

std::string GoodsModel::insert(const std::string &_name, int _num)
{
    char sql[200]={0};
    snprintf(sql,200,"insert into products(name,num) values('%s',%d)",_name.c_str(),_num);
    return sql;
}

std::string GoodsModel::deleteGoodsByName(std::string &_name)
{     
    char sql[200]={0};
    snprintf(sql,200,"delete from products where name='%s'",_name.c_str());    
    return sql;
}



std::string GoodsModel::updateGoodsNumByName(std::string &_name, int _num)
{
    char sql[200]={0};
    snprintf(sql,200,"update products set num=%d where name='%s'",_num,_name.c_str());
    return sql;
}

std::string GoodsModel::queryAllGoods()
{
    char sql[200]={"select * from products"};
    return sql;
}

std::string GoodsModel::queryByName(std::string &_name)
{
    char sql[200]={0};
    snprintf(sql,200,"select * from products where name='%s",_name.c_str());
    return sql;
}

std::vector<Goods> GoodsModel::allFieldsResToVector(MYSQL_RES *_res)
{
    std::vector<Goods> RES;
    if(_res!=nullptr)
    {
        MYSQL_ROW row;
        while((row=mysql_fetch_row(_res))!=nullptr)
        {
            RES.push_back(Goods(row[0],atoi(row[1])));
        }
        mysql_free_result(_res);
    }
    return RES;
}

std::vector<std::string> GoodsModel::allFieldsGoodsToStringInVector(std::vector<Goods> goods_info)
{
    std::vector<std::string> res;
    if(!goods_info.empty())
    {
        for(Goods &goods:goods_info)
        {
            json js;
            js["goods_name"]=goods.getName();
            js["goods_num"]=goods.getNum();
            res.push_back(js.dump());
        }
    }
    return res;
}

