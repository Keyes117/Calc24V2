#include "TCPConnection.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <cstdlib>

//#include <cerrno>

TCPConnection::TCPConnection(const std::shared_ptr<EventLoop>& spEventLoop)
    :m_spEventLoop(spEventLoop)
{
}

TCPConnection::~TCPConnection()
{
    ::close(m_fd);
}

bool TCPConnection::send(const char* buf, int bufLen)
{
    m_sendBuf.append(buf, bufLen);

   
    while (true)
    {
        int sendLength = ::send(m_fd, m_sendBuf, m_sendBuf.remaining(), 0);

        if (sendLength == 0)
        {
            //�Զ˹ر������� 
            onClose();
            return false;
        }
        else if (sendLength < 0)
        {
            if (errno == EINTR)
                continue;
            else if (errno == EWOULDBLOCK || errno == EAGAIN)
            {
                //��ǰ��������TCP����̫С�����ݷ�����ȥ
                m_writeCallback();

                registerWriteEvent();


                return true;
            }

            //����������ǳ����ˣ� �ر����� 
            onClose();
            return false;
        }

        //���ͳɹ���
        m_sendBuf.erase(sendLength);
        if (m_sendBuf.isEmpty())
            return true;
    }
  

}

bool TCPConnection::send(const std::string& buf)
{
    return send(buf.c_str(), buf.length());
}

void TCPConnection::onRead()
{
    if (!m_enableRead)
        return;

    char buf[1024];
    int recvLength = ::recv(m_fd, buf, sizeof(buf), 0);
    if (recvLength == 0)
    {
        //�Զ˹ر������� 
        //TODO:���Ƴ������¼� �ر�����
        onClose();
    }
    else if (recvLength < 0)
    {
        if (errno == EINTR)
            return;


        //����������ǳ����ˣ� �ر����� 
        onClose();
        return;
    }

    //�����յ����ݰ� 
    m_recvBuf.append(buf, recvLength);

    //���
    if (!m_readCallback(m_recvBuf))
    {
        //�ر����� 
        onClose();
    }
}

void TCPConnection::onWrite()
{
    if (!m_enableWrite)
        return;

    while (true)
    {
        int sendLength = ::send(m_fd, m_sendBuf, m_sendBuf.remaining(), 0);

        if (sendLength == 0)
        {
            //�Զ˹ر������� 
            onClose();
            return ;
        }
        else if (sendLength < 0)
        {
            if (errno == EINTR)
                continue;
            else if (errno == EWOULDBLOCK || errno == EAGAIN)
            {
                //��ǰ��������TCP����̫С�����ݷ�����ȥ
                m_writeCallback();

                registerWriteEvent();

                return ;
            }

            //����������ǳ����ˣ� �ر����� 
            onClose();
            return ;
        }

        //���ͳɹ���
        m_sendBuf.erase(sendLength);
        if (m_sendBuf.isEmpty())
            return ;
    }
}

void TCPConnection::onClose()
{
    m_closeCallback();

    unregisterAllEvent();

}

void TCPConnection::enableReadWrite(bool read, bool write)
{
    m_enableRead = read;
    m_enableWrite = write;
}

void TCPConnection::registerWriteEvent()
{
    if (m_registerWriteEvent)
        return;

    //��IO���ú���ע��д�¼� 
    m_spEventLoop->registerWriteEvents(m_fd, true);

}

void TCPConnection::unregisterWriteEvent()
{
    if (!m_registerWriteEvent)
        return;

    //��IO���ú�����ע��д�¼�

    m_spEventLoop->registerWriteEvents(m_fd, false);
    m_registerWriteEvent = false;
}

void TCPConnection::unregisterAllEvent()
{
    //��IO���ú�����ע�����ж�д�¼�
    m_spEventLoop->registerReadEvents(m_fd, false);
    m_spEventLoop->registerWriteEvents(m_fd, false);
}
