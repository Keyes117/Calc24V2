cmake_minimum_required(VERSION 3.20)

project (CALC24_Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g -Wall -O0 -Wno-unused-variable -pthread")

include_directories(
    utils/
	net/
)

link_directories(
    /lib64
)

set(net_srcs 
net/Acceptor.cpp
net/ByteBuffer.cpp
net/Epoll.cpp
net/EventLoop.cpp
net/Poll.cpp
net/Select.cpp
net/TCPConnection.cpp
net/TCPServer.cpp
net/ThreadPool.cpp
)

set(util_srcs
utils/utils.cpp
)

set(app_srcs
appsrc/Calc24Server.cpp
appsrc/Calc24Session.cpp
appsrc/main.cpp
)


add_executable(calc24Srv ${net_srcs} ${util_srcs} ${app_srcs})
#�������Ŀ¼��û�õģ�������ʹ��TARGET_LINK_LIBRARIES���Ӹÿ�
TARGET_LINK_LIBRARIES(calc24Srv)