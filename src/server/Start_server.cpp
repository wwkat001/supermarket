#include<Server.hpp>

int main(int argc,char **argv)
{
    EventLoop loop;
    InetAddress addr(atoi(argv[1]),argv[2]);
    Server server(&loop,addr,"market");
    server.start();
    loop.loop();

    return 0;
}