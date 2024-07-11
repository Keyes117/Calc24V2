#pragma once

#include "TCPServer.h"

#include <string>

#include "Calc24Session.h"

class Calc24Server final
{
public:
    Calc24Server() = default;
    ~Calc24Server() = default;


    bool init(int32_t threadNum, const std::string& ip, uint16_t port);
    void uninit();

private:
    void onConnected(std::shared_ptr<TCPConnection>& spConn);
    void onDisConnected(std::shared_ptr<TCPConnection>& spConn);

private:
    TCPServer                                       m_tcpServer;

    std::vector<std::shared_ptr<Calc24Session>>     m_sessions;
};

