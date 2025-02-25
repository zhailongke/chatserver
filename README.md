# chatserver

#### 介绍
基于nginx和redis中间件的负载均衡集群聊天服务器，以及测试用的客户端

#### 软件功能
一对一聊天服务
群聊服务
添加好友/群聊

#### 软件架构
软件架构说明
/bin 可执行文件
/build 编译生成中间件
/include 项目的头文件
/src 源码文件
/thirdparty 第三方库头文件
/test 测试第三方库文件

#### 编译方式
直接使用脚本autobuild.sh:
./autobuild.sh
使用命令行
cd build
rm -rf *
cmake ..
make