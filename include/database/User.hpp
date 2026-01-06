#pragma once

#include<string>

class User
{
    public:

    User(int _id,std::string _name,std::string _password,bool _is_manager)
    :id(_id),name(_name),password(_password),is_manager(_is_manager)
    {

    }

    private:
    int id;
    std::string name ;
    std::string password;
    bool is_manager;
};