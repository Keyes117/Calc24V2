#include "TCPConnection.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <cstdlib>

//#include <cerrno>

TCPConnection::TCPConnection()
{
}

TCPConnection::~TCPConnection()
{
}

bool TCPConnection::send(const char* buf, int bufLen)
{
    m_sendBuf.append(buf, bufLen);

    int sendLength = ::send(m_fd, m_sendBuf.c_str(), m_sendBuf.remaining(), 0);

    if (recvLength == 0)
    {
        //对端关闭了链接 
        //TODO: 关闭链接
    }
    else if (recvLength < 0)
    {
        if (errno == EINTR)
            return;
        else if (errno == EWOULDBLOCK || errno == EAGAIN)
        {
            registerWriteEvent();
            return;
        }

        //其他情况就是出错了， 关闭链接 
        return;
    }

}

bool TCPConnection::send(const std::string& buf)
{
    return false;
}

void TCPConnection::onRead()
{

    char buf[1024];
    int recvLength = ::recv(m_fd, buf, sizeof(buf), 0);
    if (recvLength == 0)
    {
        //对端关闭了链接 
        //TODO: 关闭链接
    }
    else if (recvLength < 0)
    {
        if (errno == EINTR)
            return;


        //其他情况就是出错了， 关闭链接 
        return;
    }

    //正常收到数据包 
    m_recvBuf.append(buf, recvLength);

    //解包
    if (!m_readCallback(m_recvBuf))
    {
        //关闭链接 

    }
}

void TCPConnection::onWrite()
{

}
