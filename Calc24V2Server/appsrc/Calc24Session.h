#pragma once

#include "TCPServer.h"

#include "Calc24Protocol.h"

class Calc24Session
{
public:
    Calc24Session(std::shared_ptr<TCPConnection>&& spConn);
    ~Calc24Session() = default;

     
    void onRead(ByteBuffer& recvBuf);
    void onWrite();

    void onClose();
    //ÒµÎñ´úÂë
    void sendWelcomeMsg();

private:
    bool decodePackage(ByteBuffer& recvBuf, const MsgHeader& header);



private:
    std::shared_ptr<TCPConnection>          m_conn;
};

