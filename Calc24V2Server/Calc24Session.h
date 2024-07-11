#pragma once

#include "TCPServer.h"

#include "Calc24Protocol.h"

class Calc24Session
{
public:
    Calc24Session(std::shared_ptr<TCPConnection>&& spConn);
    ~Calc24Session() = default;


    //TODO: ��� Ϊʲô����ֵ�ǲ������� 
    bool onRead(ByteBuffer& recvBuf);
    void onWrite();

    void onClose();
    //ҵ�����


private:
    bool decodePackage(ByteBuffer& recvBuf, const MsgHeader& header);

private:
    std::shared_ptr<TCPConnection>          m_conn
};

