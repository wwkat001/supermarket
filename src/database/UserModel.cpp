#include "UserModel.hpp"
#include"Log.hpp"

std::string UserModel::insert(int _id, const std::string &userName, const std::string &password, bool is_manager)
{
    char sql[200] = {0};
    snprintf(sql, 200, "insert into user(id,name,password,is_manager) values(%d,'%s','%s',%d)", _id, userName.c_str(), password.c_str(), is_manager);
    log("sql",sql);
    return sql;
}

std::string UserModel::query_for_login(int _id, const std::string &password)
{
    char sql[200] = {0};
    snprintf(sql, 200, "select * from user where id=%d and password='%s'", _id, password.c_str());
    return sql;
}

std::string UserModel::deleteByUserId(int _id)
{
    char sql[200] = {0};
    snprintf(sql, 200, "delete from user where id=%d", _id);
    return sql;
}

std::string UserModel::query_all()
{
    char sql[200] = {0};
    snprintf(sql, 200, "SELECT id,name,is_manager FROM user");
    return sql;
}

std::vector<User> UserModel::allFieldsResToVector(MYSQL_RES *_res)
{
    std::vector<User> RES;
    if (_res != nullptr)
    {
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(_res)) != nullptr)
        {
            RES.push_back(User(atoi(row[0]), row[1], row[2], atoi(row[3])));
        }
        mysql_free_result(_res);
    }
    return RES;
}

std::vector<std::string> UserModel::allFieldsUserToStringInVector(std::vector<User> user_info)
{
    std::vector<std::string> res;
    if (!user_info.empty())
    {
        for (User &user : user_info)
        {
            json js;
            js["user_id"] = user.getId();
            js["user_name"] = user.getName();
            js["is_manager"] = user.getIsManager();
            res.push_back(js.dump());
        }
    }
    return res;
}
