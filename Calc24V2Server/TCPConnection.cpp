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
}

void TCPConnection::onWrite()
{

}
