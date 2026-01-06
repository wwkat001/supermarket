#pragma once

#include"Model.hpp"
#include"User.hpp"

#include<string>
#include<vector>

class UserModel :public Model
{
    public:

    char * insert(int _id,const std::string &userName,const std::string &password,bool is_manager);

    char * query_for_login(int _id,const std::string &password);

    std::vector<User> query_all();

};