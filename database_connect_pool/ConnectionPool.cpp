#include "ConnectionPool.h"
#include<iostream>

ConnectionPool *ConnectionPool::getConnectionPool()
{
    static ConnectionPool pool;
    return &pool;
}

std::shared_ptr<Connection> ConnectionPool::getConnection()
{
    std::unique_lock<std::mutex> lock(_queueMutex);
    while(_connectionQueue.empty())
    {
        if (std::cv_status::timeout == _cv.wait_for(lock, std::chrono::milliseconds(_connectionTimeOut)))
        {
            if (_connectionQueue.empty())
            {
                // 获取超时
                return nullptr;
            }
        }
    }

    std::shared_ptr<Connection> sp(_connectionQueue.front(), [&](Connection *pcon)
                                   {
        std::unique_lock<std::mutex> lock(_queueMutex);
        pcon->refreshAliveTime();
        _connectionQueue.push(pcon); });
    _connectionQueue.pop();
    _cv.notify_all();
    return sp;
}

ConnectionPool::ConnectionPool():
_ip("127.0.0.1"),_port(3306),_userName("root"),_password("123456"),
_dbName("supermarket"),_initSize(10),_maxSize(1000),_maxIdleTIme(60),
_connectionTimeOut(100)
{
    // if (!loadConfigFile())
    // {
    //     // log加载配置失败
    //     return;
    // }

    for (int i = 0; i < _initSize; ++i)
    {
        Connection *p = new Connection();
        p->connect(_ip, _port, _userName, _password, _dbName);
        p->refreshAliveTime();
        _connectionQueue.push(p);
        _connectionCnt++;
    }

    //生产者线程
    std::thread produce(std::bind(&ConnectionPool::produceConnectionTask, this));
    produce.detach();
    //消费者线程
    std::thread scanner(std::bind(&ConnectionPool::scanConnectionTask,this));
    scanner.detach();

}

ConnectionPool::~ConnectionPool()
{
}

bool ConnectionPool::loadConfigFile()
{
    FILE *pf = fopen("mysql_connectionPool_config.cnf", "r");
    if (pf == nullptr)
    {
        // log配置文件不存在
        return false;
    }

    while (!feof(pf))
    {
        char line[100] = {0};
        fgets(line, 100, pf);
        std::string str = line;
        int idx = str.find('=', 0);
        if (idx == -1)
        {
            continue;
        }
        int endidx = str.find('\n', idx);
        std::string key = str.substr(0, idx);
        std::string value = str.substr(idx + 1, endidx - idx - 1);

        if (key == "ip")
        {
            _ip = value;
        }
        else if (key == "port")
        {
            _port = atoi(value.c_str());
        }
        else if (key == "userName")
        {
            _userName = value;
        }
        else if (key == "password")
        {
            _password = value;
        }
        else if (key == "dbName")
        {
            _dbName = value;
        }
        else if (key == "initSize")
        {
            _initSize = atoi(value.c_str());
        }
        else if (key == "maxSize")
        {
            _maxSize = atoi(value.c_str());
        }
        else if (key == "maxIdleTime")
        {
            _maxIdleTIme = atoi(value.c_str());
        }
        else if (key == "connectionTimeOut")
        {
            _connectionTimeOut = atoi(value.c_str());
        }
    }
    return true;
}

void ConnectionPool::produceConnectionTask()
{
    for (;;)
    {
        std::unique_lock<std::mutex> lock(_queueMutex);
        while (!_connectionQueue.empty())
        {
            _cv.wait(lock);
        }
        if (_connectionCnt < _maxSize)
        {
            Connection *p = new Connection();
            p->connect(_ip, _port, _userName, _password, _dbName);
            p->refreshAliveTime();
            _connectionQueue.push(p);
            _connectionCnt++;
        }

        _cv.notify_all();
    }
}

void ConnectionPool::scanConnectionTask()
{
    for(;;)
    {
        //模拟定时
        std::this_thread::sleep_for(std::chrono::milliseconds(_maxIdleTIme));

        //扫描整个队列，释放多余连接
        std::unique_lock<std::mutex> lock(_queueMutex);
        while(_connectionCnt>_initSize)
        {
            Connection *p=_connectionQueue.front();
            if(p->getAliveTime()>=(_maxIdleTIme*1000))
            {
                _connectionQueue.pop();
                _connectionCnt--;
                delete p;
            }
            else    
            {
                break;
            }
        }
    }   
}
