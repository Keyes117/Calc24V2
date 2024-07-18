#include "Calc24Server.h"

#include<functional>
#include <memory>



bool Calc24Server::init(int32_t threadNum, const std::string& ip /*="" */, uint16_t port /* =8888*/)
{

    m_tcpServer.setConnectedCallback(std::bind(Calc24Server::onConnected, this, std::placeholders::_1));

    if (!m_tcpServer.init(5, ip, port))
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
    //注意这里的左右值转换
    auto spCalc24Session = std::make_shared<Calc24Session>(std::move(spConn));
    m_sessions.push_back(std::move(spCalc24Session));
}

void Calc24Server::onDisConnected(std::shared_ptr<TCPConnection>& spConn)
{

}
