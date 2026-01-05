#pragma once

#include "Connection.h"

#include <string>
#include <queue>
#include<mutex>
#include<atomic>
#include<thread>
#include<memory>
#include<functional>
#include<condition_variable>
#include<chrono>

class ConnectionPool
{
public:
    static ConnectionPool *getConnectionPool();

    std::shared_ptr<Connection> getConnection();

    ~ConnectionPool();

private:
    ConnectionPool();

    bool loadConfigFile();

    //运行在生产者线程中，专门生产新连接
    void produceConnectionTask();

    void scanConnectionTask();

    std::string _ip;
    unsigned short _port;
    std::string _userName;
    std::string _password;
    std::string _dbName;
    int _initSize;
    int _maxSize;
    int _maxIdleTIme;
    int _connectionTimeOut;

    std::queue<Connection *> _connectionQueue;
    std::mutex _queueMutex;
    std::atomic_int _connectionCnt;
    std::condition_variable _cv;//生产者消费者线程通信
};