#pragma once

#include"Model.hpp"
#include"User.hpp"

#include<string>
#include<vector>
#include<mysql/mysql.h>

class UserModel :public Model
{
    public:

    char * insert(int _id,const std::string &userName,const std::string &password,bool is_manager);

    char * query_for_login(int _id,const std::string &password);

    char * deleteByUserId(int _id);

    std::vector<User> query_all();

    std::vector<User> allFieldsResToVector(MYSQL_RES*_res);

};