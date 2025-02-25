cmake_minimum_required(VERSION 3.0)
project(main)

#配置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

set(SRC_LIST muduo_server.cpp)

add_executable(server ${SRC_LIST})

target_link_libraries(server muduo_net muduo_base pthread)