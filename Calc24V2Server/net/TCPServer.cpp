#include "TCPServer.h"

#include <functional>

bool TCPServer::init(int32_t threadNum, const std::string& ip, uint16_t port)
{
    m_threadPool.start(threadNum);

    //TODO����ip��port��һЩ��Ҫ��У�� 
    m_ip = ip;
    m_port = port;

    m_baseEventLoop.init();

    m_acceptor = new Acceptor(&m_baseEventLoop);
    if (m_acceptor->startListen(ip, port))
        return false;

    //TODO:AcceptCallbackʵ��ֻ��һ�������� ����bind ��thisָ�� ����������
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

    //����û��� ��һЩ�Լ�������
    m_connectedCallback(spTCPConnection);

    //m_connections[clientfd] = std::move(spTCPConnection);
}

