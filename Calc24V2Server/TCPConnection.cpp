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
        //�Զ˹ر������� 
        //TODO: �ر�����
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

        //����������ǳ����ˣ� �ر����� 
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
        //�Զ˹ر������� 
        //TODO: �ر�����
    }
    else if (recvLength < 0)
    {
        if (errno == EINTR)
            return;


        //����������ǳ����ˣ� �ر����� 
        return;
    }

    //�����յ����ݰ� 
    m_recvBuf.append(buf, recvLength);

    //���
    if (!m_readCallback(m_recvBuf))
    {
        //�ر����� 

    }
}

void TCPConnection::onWrite()
{

}
