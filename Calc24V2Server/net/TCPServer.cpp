#include "TCPServer.h"

#include <functional>

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

    //TODO:AcceptCallback实际只有一个参数， 但是bind 了this指针 会有问题吗？
    m_acceptor->setAcceptCallback(std::bind(&TCPServer::onAccept, this, std::placeholders::_1));
    return true;
}

void TCPServer::uninit()
{
    m_threadPool.stop();

}

void TCPServer::start()
{
    m_baseEventLoop.run();
}

void TCPServer::onConnected(std::shared_ptr<TCPConnection>& spConn)
{
}

void TCPServer::onDisConnected(std::shared_ptr<TCPConnection>& spConn)
{
}

void TCPServer::onAccept(int clientfd)
{

    std::shared_ptr<EventLoop> spEventLoop = m_threadPool.getNextEventLoop();

    auto spTCPConnection = std::make_shared<TCPConnection>(clientfd, spEventLoop);
    spTCPConnection->startRead();

    //如果用户想 做一些自己的事情
    m_connectedCallback(spTCPConnection);

    //m_connections[clientfd] = std::move(spTCPConnection);
}

