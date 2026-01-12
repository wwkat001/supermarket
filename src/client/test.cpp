#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>

#include "json.hpp"

using json = nlohmann::json;
using namespace std;

void readFunc(int clientfd)
{
    while (true)
    {
        char recv_str[200] = {0};
        int len=recv(clientfd,recv_str,200,0);
        cout<<"recvice: "<<recv_str<<endl;
        if(len==0||len==-1)
        {
            cout<<"连接断开"<<endl;
            close(clientfd);
            exit(0);
        }  
        
    }
}

int main()
{
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server;
    memset(&server, 0, sizeof(sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(8000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(clientfd, (sockaddr *)&server, sizeof(sockaddr_in)) == -1)
    {
        perror("connect server error");
        close(clientfd);
        exit(-1);
    }
    thread r(readFunc, clientfd);
    r.detach();
    int choice = 0;
    int t;
    std::string str;
    while (true)
    {
        std::string send_str;
        char recv_str[500] = {0};
        json send_js;
        json recv_js;

        cin >> choice;
        switch (choice)
        {
        case 1:
            send_js["msg_id"] = 1;
            cin >> t;
            send_js["user_id"] = t;
            cin >> str;
            send_js["user_name"] = str;
            cin >> str;
            send_js["password"] = str;
            cin >> t;
            send_js["is_manager"] = true;
            send_str = send_js.dump();
            send(clientfd, send_str.c_str(), strlen(send_str.c_str() )+1, 0);

            break;
        case 2:
            send_js["msg_id"] = 2;

            send_str = send_js.dump();
            send(clientfd, send_str.c_str(), strlen(send_str.c_str() )+1, 0);

            break;

        case 3:
            send_js["msg_id"] = 3;
            cin >> t;
            send_js["user_id"] = t;
            cin >> str;
            send_js["password"] = str;
            send_str = send_js.dump();
            send(clientfd, send_str.c_str(), strlen(send_str.c_str() )+1, 0);

            break;

        case 4:
            send_js["msg_id"] = 4;
            cin >> str;
            send_js["goods_name"] = str;
            cin >> t;
            send_js["goods_num"] = t;
            send_str = send_js.dump();
            send(clientfd, send_str.c_str(), strlen(send_str.c_str() )+1, 0);

            break;

        case 5:
            send_js["msg_id"] = 5;
            cin >> t;
            send_js["user_id"] = t;

            send_str = send_js.dump();
            send(clientfd, send_str.c_str(), strlen(send_str.c_str() )+1, 0);

            break;
        case 6:
            send_js["msg_id"] = 6;
            cin >> str;
            send_js["goods_name"] = str;
            send_str = send_js.dump();
            send(clientfd, send_str.c_str(), strlen(send_str.c_str() )+1, 0);

            break;

        case 7:
            send_js["msg_id"] = 7;
            cin >> str;
            send_js["goods_name"] = str;
            cin >> t;
            send_js["goods_num"] = t;
            send_str = send_js.dump();
            send(clientfd, send_str.c_str(), strlen(send_str.c_str() )+1, 0);

            break;

        case 8:
            send_js["msg_id"] = 8;
            send_str = send_js.dump();
            send(clientfd, send_str.c_str(), strlen(send_str.c_str() )+1, 0);

            break;

        case 9:
            send_js["msg_id"] = 9;
            cin >> str;
            send_js["goods_name"] = str;

            send_str = send_js.dump();
            send(clientfd, send_str.c_str(), strlen(send_str.c_str() )+1, 0);

            break;

        case 10:
            send_js["msg_id"] = 10;
            cin >> str;
            send_js["goods_name"] = str;
            cin >> t;
            send_js["goods_num"] = t;

            send_str = send_js.dump();
            send(clientfd, send_str.c_str(), strlen(send_str.c_str() )+1, 0);

            break;

        case 12:
            send_js["msg_id"] = 12;
            cin >> str;
            send_js["goods_name"] = str;
            cin >> t;
            send_js["goods_num"] = t;

            send_str = send_js.dump();
            send(clientfd, send_str.c_str(), strlen(send_str.c_str() )+1, 0);

            break;
        default:
            break;
        }
        if (choice > 12)
        {
            break;
        }
    }
}
