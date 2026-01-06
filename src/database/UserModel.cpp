#include"UserModel.hpp"

char* UserModel::insert(int _id, const std::string &userName,const std::string &password, bool is_manager)
{
    char sql[200]={0};
    snprintf(sql,200,"insert into user(id,name,password,is_manager) values(%d,'%s','%s',%d)",_id,userName,password,is_manager);
    return sql;
}

char *UserModel::query_for_login(int _id, const std::string &password)
{
    char sql[200]={0};
    snprintf(sql,200,"select * from user where id=%d and password='%s'",_id,password);
    return sql;
}

std::vector<User> UserModel::query_all()
{
    char sql[200]={0};
    snprintf(sql,200,"SELECT id,name,is_manager FROM user");
    return std::vector<User>();
}
