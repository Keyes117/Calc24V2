#include "Calc24Session.h"

#include <functional>



Calc24Session::Calc24Session(std::shared_ptr<TCPConnection>&& spConn):
    m_conn(std::move(spConn))
{
    spConn->setReadCallback(std::bind(Calc24Session::onRead, this,std::placeholders::_1));
    spConn->setWriteCallback(std::bind(Calc24Session::onWrite, this));
    spConn->setCloseCallback(std::bind(Calc24Session::onClose, this));
}

void Calc24Session::onRead(ByteBuffer& recvBuf)
{
    //在EventLoop中已经做了recvBuf的判空
    while (true)
    {
        if (recvBuf.remaining() <= sizeof(MsgHeader))
            return;

        MsgHeader header;
        recvBuf.peek(reinterpret_cast<char*>(&header), sizeof(MsgHeader));

        if (!decodePackage(recvBuf, header))
            return;
    }
    
}

void Calc24Session::onWrite()
{
}

void Calc24Session::onClose()
{
}

bool Calc24Session::decodePackage(ByteBuffer& recvBuf,const MsgHeader& header)
{
    if (static_cast<MsgType>(header.msgType) == MsgType::MsgTypeWelcome)
    {
        WelcomeMsg welcomeMsg;
        recvBuf.retrieve(reinterpret_cast<char*>(&welcomeMsg), sizeof(welcomeMsg));

        //TODO:处理welcomeMsg
        return true;
    }

    return false;
}
