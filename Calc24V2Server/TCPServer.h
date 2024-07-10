/*
* 2024/7/10
* zhkeyes ����Server��
*/
#pragma once

#include "ThreadPool.h"


#include <memory>
#include <string>
#include <unordered_map>

#include "Acceptor.h"
#include "TCPConnection.h"
#include "EventLoop.h"


class TCPServer
{
public:
    TCPServer() = default;
    virtual ~TCPServer() = default;

    bool init(int32_t threadNum, const std::string& ip, uint16_t port);
    void uinit();

    void start();

private:
    //�ͻ��˵�����Ӧ����Server������AcceptorӦ��ֻ�������
    void onAccept(int clientfd);


private:
    std::string                                                 m_ip;
    uint16_t                                                    m_port;

    ThreadPool                                                  m_threadPool;

    EventLoop                                                   m_baseEventLoop;
    Acceptor*                                                   m_acceptor;
    
    std::unordered_map<int, std::shared_ptr<TCPConnection>>     m_connections;

};

