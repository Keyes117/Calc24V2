/*
* zhkeyes 2024/7/2
*/

#pragma once

#include <functional>

#include "ByteBuffer.h"
#include "IEventDispatcher.h"

using ReadCallback = std::function<bool(ByteBuffer& buf)>;

class TCPConnection : public IEventDispatcher
{
public:
    TCPConnection();
    ~TCPConnection();

    //TODO: 移动构造、 拷贝构造

    void setReadCallback(ReadCallback&& readCallback)
    {
        m_readCallback = std::move(readCallback);
    }

    bool send(const char* buf, int bufLen);
    bool send(const std::string& buf);


    virtual void onRead() override;
    virtual void onWrite() override;

    void registerWriteEvent();


private:
    int             m_fd;
    ByteBuffer      m_recvBuf;
    ByteBuffer      m_sendBuf;

    ReadCallback    m_readCallback;
};

