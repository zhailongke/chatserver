#include "chatserver.hpp"
#include "json.hpp"
#include "chatservice.hpp"

#include <functional>
#include <iostream>
#include <string>

using namespace std;
using namespace placeholders;
using json=nlohmann::json;//给命名空间起一个更短的名称
ChatServer::ChatServer(EventLoop *loop, const InetAddress &listenAddr, const string &nameArg)
    : _server(loop, listenAddr, nameArg), _loop(loop)
{
    // 注册回调函数
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

    // 设置线程数量
    _server.setThreadNum(4);
}

//启动服务器
void ChatServer::start()
{
    _server.start();
}

//上报链接相关信息的回调函数
void ChatServer::onConnection(const TcpConnectionPtr &conn)
{
    if (conn->connected())
    { 
        cout << conn->peerAddress().toIpPort() << " -> " << conn->localAddress().toIpPort() << " state: online" << endl;
    }
    else
    {
        //客户端断开连接
        ChatService::instance()->clientCloseException(conn);
        conn->shutdown();
        cout << conn->peerAddress().toIpPort() << " -> " << conn->localAddress().toIpPort() << " state:offline" << endl;
    }
}

//上报读写事件相关信息的回调函数
void ChatServer::onMessage(const TcpConnectionPtr &conn, Buffer *buffer, Timestamp time)
{
    string buf = buffer->retrieveAllAsString();
    //数据的反序列化
    json js = json::parse(buf);
    //达到目的：完全解耦网络模块和业务模块的代码，不指名道姓调用业务的方法
    //通过js["msgid"]获取-》业务处理器handler业务模块绑定的方法-》conn js time
    //基于接口和基于回调(cpp主要)
    
    auto msgHandler= ChatService::instance()->getHandler(js["msgid"].get<int>());
    //回调消息绑定好的事件处理器，来执行相应的业务处理
    msgHandler(conn,js,time);
}