/*
* 2024/7/10
* zhkeyes ∂‘Õ‚Server¿‡
*/
#pragma once

#include "ThreadPool.h"

#include "EventLoop.h"

class TCPServer
{
public:
    TCPServer() = default;
    virtual ~TCPServer() = default;

    void init(int32_t threadNum, const std::string& ip, uint16_t port);
    void uinit();

private:
    bool startListen();

private:
    int                 m_listenfd{ -1 };
    std::string         m_ip;
    uint16_t            m_port;

    ThreadPool          m_threadPool;

    EventLoop           m_baseEventLoop;


};

