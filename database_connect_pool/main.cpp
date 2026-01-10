// #include"ConnectionPool.h"
// #include"Connection.h"
// #include<iostream>

// int main()
// {
//     clock_t begin=clock();
//     ConnectionPool*cp=ConnectionPool::getConnectionPool();
//     for(int i=0;i<2000;++i)
//     {

//         char sql[200]={0};
//         sprintf(sql,"insert into test(id,name) values(%d,'%s')",1,"zhangsan");

//         // Connection conn;
//         // conn.connect("127.0.0.1",3306,"root","123456","mysql_learning");
//         // conn.update(sql);

//         std::shared_ptr<Connection> sp=cp->getConnection();
//         sp->update(sql);
//     }
//     clock_t end=clock();
//     std::cout<<"time:  "<<(float)(end-begin)/CLOCKS_PER_SEC<<""<<std::endl;
// }