#include "TCPServer.h"


void TCPServer::init(int32_t threadNum, const std::string& ip, uint16_t port)
{
    m_threadPool.start(threadNum);

    //TODO：做一些必要的校验 
    m_ip = ip;
    m_port = port;

    startListen();
}

void TCPServer::uinit()
{
    m_threadPool.stop();

    if (m_listenfd != -1)
    {
        ::close(m_listenfd);
        m_listenfd = -1;
    }
}

bool TCPServer::startListen()
{
    m_listenfd = ::socket(AF_INET, SOCKET_STREAM, 0);
    if (m_listenfd == -1)
        return false;

    int optval = 1;
    ::setsockopt(m_listenfd, SOL_SOCKET, SO_REUSEADDR, &optval, static_cast<socklen_t>(sizeof optval));
    ::setsockopt(m_listenfd, SOL_SOCKET, SO_REUSEPORT, &optval, static_cast<socklen_t>(sizeof optval));

    struct socketaddr_in bindaddr;
    bindaddr.sin_family = AF_INET;
    bindaddr.sin_addr.s_addr = m_ip/*htonl(INADDR_ANY)*/;
    bindaddr.sin_port = htonl(m_port);

    if (::bind(m_listenfd, (struct sockaddr*)&bindaddr, sizeof(bindaddr)) == -1)
        return false;

    if (::listen(m_listenfd, SOMAXCONN) == -1)
        return false;
}
