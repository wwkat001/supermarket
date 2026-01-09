#pragma once

#include"Model.hpp"
#include"User.hpp"

class UserModel :public Model
{
    public:

    char * insert(int _id,const std::string &userName,const std::string &password,bool is_manager);

    char * query_for_login(int _id,const std::string &password);

    char * deleteByUserId(int _id);

    char * query_all();

    std::vector<User> allFieldsResToVector(MYSQL_RES*_res);

    std::vector<std::string> allFieldsUserToStringInVector(std::vector<User> user_info);

};