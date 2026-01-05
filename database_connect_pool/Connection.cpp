#include "Connection.h"

Connection::Connection():
_conn(mysql_init(nullptr))
{
    
}

Connection::~Connection()
{
    if(_conn!=nullptr)
    {
        mysql_close(_conn);
    }
}

bool Connection::connect(const std::string &ip,
     const unsigned short &port, 
     const std::string &user,
      const std::string &password, 
      const std::string &dbname)
{
    MYSQL*p=mysql_real_connect(_conn,ip.c_str(),user.c_str(),password.c_str(),dbname.c_str(),port,nullptr,0);
    return p!=nullptr;
}

bool Connection::update(const std::string &sql)
{
    if(mysql_query(_conn,sql.c_str()))
    {
        //log更新失败信息
        return false;
    }
    return true;
}

MYSQL_RES *Connection::query(const std::string &sql)
{
    if(mysql_query(_conn,sql.c_str()))
    {
        //log查询失败信息
        return nullptr;
    }
    return mysql_use_result(_conn);
}
