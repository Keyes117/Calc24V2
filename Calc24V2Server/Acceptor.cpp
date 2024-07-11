#include "Acceptor.h"

Acceptor::Acceptor(EventLoop* pEventLoop):
    m_pEventLoop(pEventLoop)
{
}

Acceptor::~Acceptor()
{
    if (m_listenfd != -1)
    {
        ::close(m_listenfd);
        m_listenfd = -1;
    }
}

void Acceptor::onRead()
{
    while (true)
    {
        struct sockaddr_in clientAddr;
        socklen_t clientAddrlen = sizeof(clientaddr);
        //4. 接受客户端连接
        int clientfd = ::accept4(m_listenfd, (struct sockaddr*)&clientAddr, &clientAddrlen, SOCK_NONBLOCK);

        if (clientfd > 0)
        {
            //成功接收链接 
            m_acceptCallback(clientfd);

        }
        else if (clientfd == -1)
        {
            //没有连接
            if (errno = EWOULDBLOCK)
                return;
            else
                return;
        }
        
    }
   
}

bool Acceptor::startListen(const std::string& ip, uint16_t port)
{
    //1.创建一个侦听socket
    m_listenfd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (m_listenfd == -1)
    {
        std::cout << "create listen socket error." << std::endl;
        return false;
    }
    //端口号复用
    int optval = 1;
    //TODO: 判断函数是否调用成功
    ::setsockopt(m_listenfd, SOL_SOCKET, SO_REUSEADDR, &optval, static_cast<socklen_t>(sizeof optval));
    ::setsockopt(m_listenfd, SOL_SOCKET, SO_REUSEPORT, &optval, static_cast<socklen_t>(sizeof optval));


    //2.初始化服务器地址
    struct sockaddr_in bindaddr;
    bindaddr.sin_family = AF_INET;
    //TODO: 待修复
    bindaddr.sin_addr.s_addr = ip/*htonl(INADDR_ANY)*/;
    bindaddr.sin_port = port;
    if (::bind(m_listenfd, (struct sockaddr*)&bindaddr, sizeof(bindaddr)) == -1)
    {
        std::cout << "bind listen socket error." << std::endl;
        return false;
    }


    //3.启动侦听
    if (::listen(m_listenfd, SOMAXCONN) == -1)
    {
        std::cout << "listen error." << std::endl;
        return false;
    }

    m_pEventLoop->registerReadEvents(m_listenfd, true);

    return true;
}
