#pragma once

#include "TCPServer.h"

#include "Calc24Protocol.h"

class Calc24Session
{
public:
    Calc24Session(std::shared_ptr<TCPConnection>&& spConn);
    ~Calc24Session() = default;


    //TODO: 检查 为什么返回值是布尔类型 
    bool onRead(ByteBuffer& recvBuf);
    void onWrite();

    void onClose();
    //业务代码


private:
    bool decodePackage(ByteBuffer& recvBuf, const MsgHeader& header);

private:
    std::shared_ptr<TCPConnection>          m_conn
};

