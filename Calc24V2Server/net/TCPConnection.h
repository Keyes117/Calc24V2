/*
* zhkeyes 2024/7/2
*/

#pragma once

#include <functional>
#include <memory>

#include "ByteBuffer.h"
#include "EventLoop.h"
#include "IEventDispatcher.h"

//ReadCallback 如果返回false 表示上层业务逻辑认为 处理出错， 希望关闭连接
using ReadCallback = std::function<bool(ByteBuffer& buf)>;
using WriteCallback = std::function<void()>;
using CloseCallback = std::function<void()>;


class TCPConnection : public IEventDispatcher
{
public:
    TCPConnection(int clientfd,const std::shared_ptr<EventLoop>& spEventLoop);
    virtual ~TCPConnection();

    bool startRead();

    TCPConnection(const TCPConnection& rhs);
    TCPConnection& operator=(const TCPConnection& rhs);

    TCPConnection(TCPConnection&& rhs) noexcept;
    TCPConnection& operator=(TCPConnection&& rhs);



    void setReadCallback(ReadCallback&& readCallback)
    {
        m_readCallback = std::move(readCallback);
    }

    void setWriteCallback(WriteCallback&& writeCallback)
    {
        m_writeCallback = std::move(writeCallback);
    }

    void setCloseCallback(CloseCallback&& closeCallback)
    {
        m_closeCallback = std::move(closeCallback);
    }


    bool send(const char* buf, int bufLen);
    bool send(const std::string& buf);


    virtual void onRead() override;
    virtual void onWrite() override;

    virtual void onClose() override;

    virtual void enableReadWrite(bool read, bool write) override;

private:
    void registerWriteEvent();
    void unregisterWriteEvent();


    void unregisterAllEvent();


private:
    int                             m_fd;
    bool                            m_registerWriteEvent{ false };
    bool                            m_isListenfd{ false }; //TODO：如果是侦听fd呢？
    bool                            m_enableRead{ false };
    bool                            m_enableWrite{ false };

    ByteBuffer                      m_recvBuf;
    ByteBuffer                      m_sendBuf;

    ReadCallback                    m_readCallback;
    WriteCallback                   m_writeCallback;
    CloseCallback                   m_closeCallback;

    std::shared_ptr<EventLoop>      m_spEventLoop;

};

