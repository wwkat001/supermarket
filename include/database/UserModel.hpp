#pragma once

#include"Model.hpp"
#include"User.hpp"

class UserModel :public Model
{
    public:

    std::string insert(int _id,const std::string &userName,const std::string &password,bool is_manager);

    std::string query_for_login(int _id,const std::string &password);

    std::string deleteByUserId(int _id);

    std::string query_all();

    std::vector<User> allFieldsResToVector(MYSQL_RES*_res);

    std::vector<std::string> allFieldsUserToStringInVector(std::vector<User> user_info);

};