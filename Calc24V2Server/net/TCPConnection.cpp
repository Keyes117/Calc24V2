#include "TCPConnection.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <cstdlib>

//#include <cerrno>

TCPConnection::TCPConnection(int clientfd, const std::shared_ptr<EventLoop>& spEventLoop):
    m_fd(clientfd),
    m_spEventLoop(spEventLoop)    
{

}

TCPConnection::~TCPConnection()
{
    ::close(m_fd);
}

bool TCPConnection::startRead()
{
    m_spEventLoop->registerReadEvents(m_fd, true);
}

TCPConnection::TCPConnection(const TCPConnection& rhs) :
    m_fd(rhs.m_fd),
    m_registerWriteEvent(rhs.m_registerWriteEvent),
    m_isListenfd(rhs.m_isListenfd),
    m_enableRead(rhs.m_enableRead),
    m_enableWrite(rhs.m_enableWrite),
    m_recvBuf(rhs.m_recvBuf),
    m_sendBuf(rhs.m_sendBuf),
    m_readCallback(rhs.m_readCallback),
    m_writeCallback(rhs.m_writeCallback),
    m_closeCallback(rhs.m_closeCallback),
    m_spEventLoop(rhs.m_spEventLoop)
{


}

// ������ֵ�����
TCPConnection& TCPConnection::operator=(const TCPConnection& rhs) {
    if (this != &rhs) {
        m_fd = rhs.m_fd;
        m_registerWriteEvent = rhs.m_registerWriteEvent;
        m_isListenfd = rhs.m_isListenfd;
        m_enableRead = rhs.m_enableRead;
        m_enableWrite = rhs.m_enableWrite;
        m_recvBuf = rhs.m_recvBuf;
        m_sendBuf = rhs.m_sendBuf;
        m_readCallback = rhs.m_readCallback;
        m_writeCallback = rhs.m_writeCallback;
        m_closeCallback = rhs.m_closeCallback;
        m_spEventLoop = rhs.m_spEventLoop;
    }
    return *this;
}

// �ƶ����캯��
TCPConnection::TCPConnection(TCPConnection&& rhs) noexcept
    : m_fd(rhs.m_fd),
    m_registerWriteEvent(rhs.m_registerWriteEvent),
    m_isListenfd(rhs.m_isListenfd),
    m_enableRead(rhs.m_enableRead),
    m_enableWrite(rhs.m_enableWrite),
    m_recvBuf(std::move(rhs.m_recvBuf)),
    m_sendBuf(std::move(rhs.m_sendBuf)),
    m_readCallback(std::move(rhs.m_readCallback)),
    m_writeCallback(std::move(rhs.m_writeCallback)),
    m_closeCallback(std::move(rhs.m_closeCallback)),
    m_spEventLoop(std::move(rhs.m_spEventLoop)) {
    rhs.m_fd = -1;
    rhs.m_registerWriteEvent = false;
    rhs.m_isListenfd = false;
    rhs.m_enableRead = false;
    rhs.m_enableWrite = false;
}

// �ƶ���ֵ�����
TCPConnection& TCPConnection::operator=(TCPConnection&& rhs) noexcept {
    if (this != &rhs) {
        m_fd = rhs.m_fd;
        m_registerWriteEvent = rhs.m_registerWriteEvent;
        m_isListenfd = rhs.m_isListenfd;
        m_enableRead = rhs.m_enableRead;
        m_enableWrite = rhs.m_enableWrite;
        m_recvBuf = std::move(rhs.m_recvBuf);
        m_sendBuf = std::move(rhs.m_sendBuf);
        m_readCallback = std::move(rhs.m_readCallback);
        m_writeCallback = std::move(rhs.m_writeCallback);
        m_closeCallback = std::move(rhs.m_closeCallback);
        m_spEventLoop = std::move(rhs.m_spEventLoop);

        rhs.m_fd = -1;
        rhs.m_registerWriteEvent = false;
        rhs.m_isListenfd = false;
        rhs.m_enableRead = false;
        rhs.m_enableWrite = false;
    }
    return *this;
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
    //m_readCallback=>Calc24Session::onRead
    m_readCallback(m_recvBuf);
   
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
            return;
        }
        else if (sendLength < 0)
        {
            if (errno == EINTR)
                continue;
            else if (errno == EWOULDBLOCK || errno == EAGAIN)
            {
                //��ǰ��������TCP����̫С�����ݷ�����ȥ
                m_writeCallback();

                unregisterWriteEvent();

                return;
            }

            //����������ǳ����ˣ� �ر����� 
            onClose();
            return;
        }

        //���ͳɹ���
        m_sendBuf.erase(sendLength);
        if (m_sendBuf.isEmpty())
            return;
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
    m_spEventLoop->registerWriteEvents(m_fd,this, true);

}

void TCPConnection::unregisterWriteEvent()
{
    if (!m_registerWriteEvent)
        return;

    //��IO���ú�����ע��д�¼�

    m_spEventLoop->registerWriteEvents(m_fd,this, false);
    m_registerWriteEvent = false;
}

void TCPConnection::unregisterAllEvent()
{
    //��IO���ú�����ע�����ж�д�¼�
    m_spEventLoop->unregisterAllEvents(m_fd, this);

}
