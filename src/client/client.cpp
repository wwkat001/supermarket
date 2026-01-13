#include "Goods.hpp"
#include "User.hpp"
#include "json.hpp"

#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <iostream>
#include <signal.h>
#include <semaphore.h>

using json = nlohmann::json;

int clientfd = 0;
int user_id=0;
sem_t rwsem;
std::vector<User> usersInfo;
std::vector<Goods> goodsInfo;
bool __is_manager = false;
bool is_login = false;

int tnum;
std::string tstr1;
std::string tstr2;
bool tbool;

void QuitHander(int);

inline void fresh();

void startMenu();
void userMenu();
void managerMenu();

bool numberValid();
bool stringValid();

void cinUserId(json &js);
void cinUserName(json &js);
void cinPassword(json &js);
void cinIsManager(json &js);
void cinGoodsName(json &js);
void cinGoodsNum(json &js);

void send1();
void send2();
void send3();
void send4();
void send5();
void send6();
void send7();
void send8();
void send9();
void send10();
void send12();

void readThread(int clientfd, bool debug);

void registerResponse(json &js);

void loginResponse(json &js);

void parseGoodsInfo(json &js);
void printGoodsInfo();

void parseUserInfo(json &js);
void printUserInfo();

void actionResponse(json &js);

int main(int argc, char **argv)
{
    char *ip = "127.0.0.1";
    uint16_t port = 8000;
    if (argc < 2)
    {
    }
    else
    {
        ip = argv[1];
        port = atoi(argv[2]);
    }

    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd == -1)
    {
        std::cerr << "socket create error" << std::endl;
        exit(-1);
    }

    sockaddr_in server;
    memset(&server, 0, sizeof(sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip);

    if (connect(clientfd, (sockaddr *)&server, sizeof(sockaddr_in)) == -1)
    {
        perror("connect server error");
        close(clientfd);
        exit(-1);
    }

    sem_init(&rwsem, 0, 0);

    std::thread read(readThread, clientfd, true);
    read.detach();

    for (;;)
    {
        if (!is_login)
        {
            startMenu();
        }
        else
        {
            if (__is_manager)
            {
                managerMenu();
            }
            else
            {
                userMenu();
            }
        }
    }
}

void QuitHander(int)
{

    exit(0);
}

inline void systemCls()
{
    std::cout << "按回车键清屏..." << std::endl;

    std::string dummy;
    std::getline(std::cin, dummy);

    system("clear");
}

void startMenu()
{
    std::cout << "================" << std::endl;
    std::cout << "1.登陆" << std::endl;
    std::cout << "2.注册" << std::endl;
    std::cout << "3.退出" << std::endl;
    std::cout << "================" << std::endl;
    std::cout << "选项 : ";
    int choice = 0;
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        send3();
        break;
    case 2:
        send1();
        break;
    case 3:
        exit(0);
    default:
        break;
    }
}

void userMenu()
{
    while (true)
    {
        std::cout << "================" << std::endl;
        std::cout << "1.商品销售" << std::endl;
        std::cout << "2.进货" << std::endl;
        std::cout << "3.查询所有货物信息" << std::endl;
        std::cout << "4.精准查询货物信息" << std::endl;
        std::cout << "5.退出" << std::endl;
        std::cout << "================" << std::endl;
        std::cout << "选项 : ";
        int choice = 0;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            send10();
            break;
        case 2:
            send12();
            break;
        case 3:
            send8();
            break;
        case 4:
            send9();
            break;
        case 5:
            exit(0);
            break;
        default:
            break;
        }
    }
}

void managerMenu()
{
    std::cout << "================" << std::endl;
    std::cout << "1.查询所有用户信息" << std::endl;
    std::cout << "2.删除用户" << std::endl;
    std::cout << "3.查询所有商品信息" << std::endl;
    std::cout << "4.精准查询商品信息" << std::endl;
    std::cout << "5.删除商品" << std::endl;
    std::cout << "6.添加商品" << std::endl;
    std::cout << "7.更改商品数量" << std::endl;
    std::cout << "8.退出" << std::endl;
    std::cout << "================" << std::endl;
    std::cout << "选项 : ";
    int choice = 0;
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        send2();
        break;
    case 2:
        send5();
        break;
    case 3:
        send8();
        break;
    case 4:
        send9();
        break;
    case 5:
        send6();
        break;
    case 6:
        send4();
        break;
    case 7:
        send7();
        break;
    case 8:
        exit(0);
    default:
        break;
    }
}

bool numberValid()
{
    std::cin >> tstr1;
    if (tstr1.size() > 8)
    {
        return false;
    }
    return std::all_of(tstr1.begin(), tstr1.end(),
                       [](char c)
                       { return std::isdigit(c); });
}

bool stringValid()
{
    std::cin >> tstr2;
    if (tstr2.size() > 20)
    {
        return false;
    }
    return true;
}

void cinUserId(json &js)
{
    std::cout << "账号(不大于8位):";
    if (!numberValid())
    {
        std::cout << "非法输入" << std::endl;
        return;
    }
    js["user_id"] = atoi(tstr1.c_str());
}

void cinUserName(json &js)
{
    std::cout << "用户名(不大于20位):";
    if (!stringValid())
    {
        std::cout << "非法输入" << std::endl;
        return;
    }
    js["user_name"] = tstr2;
}

void cinPassword(json &js)
{
    std::cout << "密码(不大于20位):";
    if (!stringValid())
    {
        std::cout << "非法输入" << std::endl;
        return;
    }
    js["password"] = tstr2;
}

void cinIsManager(json &js)
{
    std::cout << "是否为管理员(0或1):";
    std::cin >> tstr1;
    if (!(tstr1[0] == '1' || tstr1[0] == '0'))
    {
        std::cout << "非法输入" << std::endl;
        return;
    }
    if (tstr1[0] == '1')
    {
        js["is_manager"] = true;
    }
    else
    {
        js["is_manager"] = false;
    }
}

void cinGoodsName(json &js)
{
    std::cout << "商品名(不大于20位):";
    if (!stringValid())
    {
        std::cout << "非法输入" << std::endl;
        return;
    }
    js["goods_name"] = tstr2;
}

void cinGoodsNum(json &js)
{
    std::cout << "数量(有效数字):";
    if (!numberValid())
    {
        std::cout << "非法输入" << std::endl;
        return;
    }
    js["goods_num"] = atoi(tstr1.c_str());
}

void send1()
{
    json sendjs;
    sendjs["msg_id"] = 1;

    cinUserId(sendjs);
    cinUserName(sendjs);
    cinPassword(sendjs);
    cinIsManager(sendjs);

    std::string sendbuf = sendjs.dump();
    send(clientfd, sendbuf.c_str(), strlen(sendbuf.c_str()), 0);
}

void send2()
{
    json sendjs;
    sendjs["msg_id"] = 2;

    std::string sendbuf = sendjs.dump();
    send(clientfd, sendbuf.c_str(), strlen(sendbuf.c_str()), 0);
}

void send3()
{
    json sendjs;
    sendjs["msg_id"] = 3;

    cinUserId(sendjs);
    user_id=sendjs["user_id"].get<int>();
    cinPassword(sendjs);

    std::string sendbuf = sendjs.dump();
    send(clientfd, sendbuf.c_str(), strlen(sendbuf.c_str()), 0);
    std::cout << "等待登陆中........" << std::endl;
    sem_wait(&rwsem);
}

void send4()
{
    json sendjs;
    sendjs["msg_id"] = 4;

    cinGoodsName(sendjs);
    cinGoodsNum(sendjs);

    std::string sendbuf = sendjs.dump();
    send(clientfd, sendbuf.c_str(), strlen(sendbuf.c_str()), 0);
}

void send5()
{
    json sendjs;
    sendjs["msg_id"] = 5;

    cinUserId(sendjs);
    if(user_id==sendjs["user_id"].get<int>())
    {
        std::cout<<"不可删除自己账号!!!!!"<<std::endl;
        return;
    }
    std::string sendbuf = sendjs.dump();
    send(clientfd, sendbuf.c_str(), strlen(sendbuf.c_str()), 0);
}

void send6()
{
    json sendjs;
    sendjs["msg_id"] = 6;

    cinGoodsName(sendjs);

    std::string sendbuf = sendjs.dump();
    send(clientfd, sendbuf.c_str(), strlen(sendbuf.c_str()), 0);
}

void send7()
{
    json sendjs;
    sendjs["msg_id"] = 7;

    cinGoodsName(sendjs);
    cinGoodsNum(sendjs);

    std::string sendbuf = sendjs.dump();
    send(clientfd, sendbuf.c_str(), strlen(sendbuf.c_str()), 0);
}

void send8()
{
    json sendjs;
    sendjs["msg_id"] = 8;

    std::string sendbuf = sendjs.dump();
    send(clientfd, sendbuf.c_str(), strlen(sendbuf.c_str()), 0);
}

void send9()
{
    json sendjs;
    sendjs["msg_id"] = 9;

    cinGoodsName(sendjs);

    std::string sendbuf = sendjs.dump();
    send(clientfd, sendbuf.c_str(), strlen(sendbuf.c_str()), 0);
}

void send10()
{
    json sendjs;
    sendjs["msg_id"] = 10;

    cinGoodsName(sendjs);
    cinGoodsNum(sendjs);

    std::string sendbuf = sendjs.dump();
    send(clientfd, sendbuf.c_str(), strlen(sendbuf.c_str()), 0);
}

void send12()
{
    json sendjs;
    sendjs["msg_id"] = 12;

    cinGoodsName(sendjs);
    cinGoodsNum(sendjs);

    std::string sendbuf = sendjs.dump();
    send(clientfd, sendbuf.c_str(), strlen(sendbuf.c_str()), 0);
}

void readThread(int clientfd, bool debug)
{
    while (true)
    {
        char recv_str[1024] = {0};
        int len = recv(clientfd, recv_str, 1024, 0);
        if (debug)
        {
            std::cout << "recvice: " << recv_str << std::endl;
        }
        if (len == 0 || len == -1)
        {
            std::cout << "连接断开" << std::endl;
            close(clientfd);
            exit(0);
        }

        json js = json::parse(recv_str);
        int choice = js["msg_id"].get<int>();
        switch (choice)
        {
        case 11:
            registerResponse(js);
            break;
        case 21:
            parseUserInfo(js);
            printUserInfo();
            break;
        case 31:
            loginResponse(js);
            break;
        case 41:
        case 51:
        case 61:
        case 71:
            actionResponse(js);
            break;
        case 81:
        case 91:
        case 101:
        case 121:
            parseGoodsInfo(js);
            printGoodsInfo();
            break;
        default:
            break;
        }
    }
}

void registerResponse(json &js)
{
    if (js["success"].get<int>() == true)
    {
        std::cout << "注册成功!!!" << std::endl;
    }
    else
    {
        std::string errmsg = js["error_msg"];
        std::cout << "注册失败!!!" << std::endl
                  << "错误信息:" << errmsg << std::endl;
    }
}

void loginResponse(json &js)
{
    if (js["success"].get<int>() == true)
    {
        sem_post(&rwsem);
        is_login = true;
        if (js["is_manager"].get<bool>() == true)
        {
            __is_manager = true;
            std::cout << "登陆成功(管理员)!!!" << std::endl;
        }
        else
        {
            std::cout << "登陆成功!!!" << std::endl;
        }
    }
    else
    {
        std::cout << "账号或密码错误" << std::endl;
        sem_post(&rwsem);
    }
}

void parseGoodsInfo(json &js)
{
    goodsInfo.clear();
    if (js.contains("goods_info"))
    {
        std::vector<std::string> vec = js["goods_info"];
        for (std::string &str : vec)
        {
            json tmp = json::parse(str);
            Goods goods(tmp["goods_name"], tmp["goods_num"].get<int>());
            goodsInfo.push_back(goods);
        }
    }
    else
    {
        std::cout<<"查询结果为空"<<std::endl;
    }
}

void printGoodsInfo()
{
    std::cout << "-商品名-|--数量--|" << std::endl;
    for (int i = 0; i < goodsInfo.size(); ++i)
    {
        std::cout << goodsInfo[i].getName() << "\t" << goodsInfo[i].getNum() << std::endl;
    }
    std::cout << "------------------" << std::endl;
}

void parseUserInfo(json &js)
{
    usersInfo.clear();
    if (js.contains("users_info"))
    {
        std::vector<std::string> vec = js["users_info"];
        for (std::string &str : vec)
        {
            json tmp = json::parse(str);
            User user(tmp["user_id"].get<int>(), tmp["user_name"], tmp["is_manager"].get<bool>());
            usersInfo.push_back(user);
        }
    }
}

void printUserInfo()
{
    std::cout << "-用户id-|-用户名-|is_manager" << std::endl;
    for (int i = 0; i < usersInfo.size(); ++i)
    {
        std::cout << usersInfo[i].getId() << "\t" << usersInfo[i].getName() << "\t" << usersInfo[i].getIsManager() << std::endl;
    }
    std::cout << "----------------------------" << std::endl;
}

void actionResponse(json &js)
{
    if (js["success"].get<int>())
    {
        std::cout << "操作成功" << std::endl;
    }
    else
    {
        std::cout << "操作失败" << std::endl;
    }
}
