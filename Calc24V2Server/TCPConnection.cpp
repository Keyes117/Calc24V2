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
            //对端关闭了链接 
            onClose();
            return false;
        }
        else if (sendLength < 0)
        {
            if (errno == EINTR)
                continue;
            else if (errno == EWOULDBLOCK || errno == EAGAIN)
            {
                //当前数据由于TCP窗口太小，数据发不出去
                m_writeCallback();

                registerWriteEvent();


                return true;
            }

            //其他情况就是出错了， 关闭链接 
            onClose();
            return false;
        }

        //发送成功了
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
        //对端关闭了链接 
        //TODO:先移除所有事件 关闭链接
        onClose();
    }
    else if (recvLength < 0)
    {
        if (errno == EINTR)
            return;


        //其他情况就是出错了， 关闭链接 
        onClose();
        return;
    }

    //正常收到数据包 
    m_recvBuf.append(buf, recvLength);

    //解包
    if (!m_readCallback(m_recvBuf))
    {
        //关闭链接 
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
            //对端关闭了链接 
            onClose();
            return ;
        }
        else if (sendLength < 0)
        {
            if (errno == EINTR)
                continue;
            else if (errno == EWOULDBLOCK || errno == EAGAIN)
            {
                //当前数据由于TCP窗口太小，数据发不出去
                m_writeCallback();

                registerWriteEvent();

                return ;
            }

            //其他情况就是出错了， 关闭链接 
            onClose();
            return ;
        }

        //发送成功了
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

    //向IO复用函数注册写事件 
    m_spEventLoop->registerWriteEvents(m_fd, true);

}

void TCPConnection::unregisterWriteEvent()
{
    if (!m_registerWriteEvent)
        return;

    //向IO复用函数反注册写事件

    m_spEventLoop->registerWriteEvents(m_fd, false);
    m_registerWriteEvent = false;
}

void TCPConnection::unregisterAllEvent()
{
    //向IO复用函数反注册所有读写事件
    m_spEventLoop->registerReadEvents(m_fd, false);
    m_spEventLoop->registerWriteEvents(m_fd, false);
}
