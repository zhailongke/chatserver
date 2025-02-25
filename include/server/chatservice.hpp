#ifndef CHATSERVICE_HPP
#define CHATSERVICE_HPP

#include <muduo/base/Logging.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/InetAddress.h>

#include <unordered_map>
#include <functional>
#include <mutex>

using namespace std;
using namespace muduo;
using namespace muduo::net;

#include "json.hpp"
#include "usermodel.hpp"
#include "offlinemessagemodel.hpp"
#include "friendmodel.hpp"
#include "groupmodel.hpp"
#include "redis.hpp"
using json = nlohmann::json;

// 表示处理消息的事件回调方法类型
using MsgHandler = std::function<void(const TcpConnectionPtr &conn,
                                      json &js,
                                      Timestamp)>;

// 聊天服务器业务类
class ChatService
{
public:
    // 获取单例对象的接口函数
    static ChatService *instance();
    // 处理登录业务
    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 处理注册业务
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 处理注销业务
    void loginout(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //一对一聊天业务
    void oneChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //添加好友业务
    void addFriend(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //创建群聊业务
    void createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //加入群聊业务
    void addGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //群聊业务
    void groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //服务器异常，业务处置方法
    void reset();
    //处理客户端异常退出
    void clientCloseException(const TcpConnectionPtr &conn);
    //处理redis订阅发布消息的回调
    void handleRedisSubscribeMessage(int, string);
    // 获取消息对应的处理器
    MsgHandler getHandler(int msgid);
    
private:
    ChatService();

    // 存储消息id和业务函数的容器
    unordered_map<int, MsgHandler> _msgHandlerMap;

    //存储在线用户的通信连接
    unordered_map<int, TcpConnectionPtr> _userConnMap;

    // 互斥锁，保证_userConnMap的线程安全
    mutex _connMutex;

    //数据操作类对象
    //每个业务是一个对象
    UserModel _userModel;
    OfflineMsgModel _offlineMsgModel;
    FriendModel _friendModel;
    GroupModel _groupModel;

    //redis操作对象
    Redis _redis;
};

#endif