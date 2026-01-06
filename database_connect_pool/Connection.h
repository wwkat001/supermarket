#pragma once

#include<mysql/mysql.h>
#include<string>
#include<ctime>

#include"Model.hpp"

class Connection
{
    public:
    Connection();
    ~Connection();
    bool connect(const std::string &ip,
        const unsigned short &port,
        const std::string &user,
        const std::string &password,
        const std::string &dbname);

    bool update(const std::string &sql);

    MYSQL_RES* query(const std::string &sql);

    bool update(const char *sql);

    MYSQL_RES* query(const char *sql);

    void refreshAliveTime(){_aliveTime=clock();};

    clock_t getAliveTime(){return clock()-_aliveTime;};

    private:
    MYSQL* _conn;
    clock_t _aliveTime;//记录进入空闲状态的时间 

};