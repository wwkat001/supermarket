#pragma once

#include<string>

class Goods
{
    public:
    Goods(const std::string &_name,int _num):name(_name),num(_num)
    {

    };

    private:
    std::string name;
    int num;
    
};