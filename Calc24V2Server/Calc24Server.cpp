#include "Calc24Server.h"

#include<functional>
#include <memory>



bool Calc24Server::init(int32_t threadNum, const std::string& ip, uint16_t port)
{
    m_tcpServer.setConnectedCallback(std::bind(Calc24Server::onConnected,this,std::placeholders::_1);

    if (!m_tcpServer.init(5,"0.0.0.0",8888))
    {
        return false;
    }
    m_tcpServer.start();

    return true;
}

void Calc24Server::uninit()
{
    m_tcpServer.uninit();
}

void Calc24Server::onConnected(std::shared_ptr<TCPConnection>& spConn)
{
    //ע�����������ֵת��
    auto spCalc24Session = std::make_shared<Calc24Session>(std::move(spConn));
    m_sessions.push_back(std::move(spCalc24Session));
}

void Calc24Server::onDisConnected(std::shared_ptr<TCPConnection>& spConn)
{
}
