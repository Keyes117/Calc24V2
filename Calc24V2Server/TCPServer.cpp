#include "TCPServer.h"



bool TCPServer::init(int32_t threadNum, const std::string& ip, uint16_t port)
{
    m_threadPool.start(threadNum);

    //TODO：对ip和port做一些必要的校验 
    m_ip = ip;
    m_port = port;

    m_baseEventLoop.init();

    m_acceptor = new Acceptor(&m_baseEventLoop);
    if (m_acceptor->startListen(ip, port))
        return false;


    return true;
}

void TCPServer::uinit()
{
    m_threadPool.stop();

  
}

void TCPServer::start()
{
    m_baseEventLoop.run();
}

void TCPServer::onAccept(int clientfd)
{
    auto spTCPConnection = std::make_shared<TCPConnection>(clientfd);

    m_connections[clientfd] = std::move(spTCPConnection);

    std::shared_ptr<EventLoop> spEventLoop = m_threadPool.getNextEventLoop();
    spEventLoop->registerReadEvents(clientfd,true);
    
}

