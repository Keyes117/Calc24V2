/*
* zhkeyes 2024/7/2
*/

#pragma once

#include <functional>

#include "ByteBuffer.h"
#include "IEventDispatcher.h"

using ReadCallback = std::function<void(ByteBuffer& buf)>;

class TCPConnection : public IEventDispatcher
{
public:
    TCPConnection();
    ~TCPConnection();

    //TODO: 移动构造、 拷贝构造

    void setReadCallback(ReadCallback&& readCallback)
    {

    }


    virtual void onRead() override;
    virtual void onWrite() override;


private:
    int             m_fd;
    ByteBuffer      m_recvBuf;

    ReadCallback    m_readCallback;
};

