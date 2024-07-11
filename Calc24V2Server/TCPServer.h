/*
* 2024/7/10
* zhkeyes 对外Server类
*/
#pragma once

#include "ThreadPool.h"


#include <memory>
#include <string>
#include <unordered_map>

#include "Acceptor.h"
#include "TCPConnection.h"
#include "EventLoop.h"

using onConnectedCallback = std::function<void(std::shared_ptr<TCPConnection>& spConn)>;
using onDisConnectedCallback = std::function<void(std::shared_ptr<TCPConnection>& spConn)>;

class TCPServer
{
public:
    TCPServer() = default;
    virtual ~TCPServer() = default;

    bool init(int32_t threadNum, const std::string& ip, uint16_t port);
    void uninit();

    void start();

    void setConnectedCallback(onDisConnectedCallback&& callback)
    {
        m_connectedCallback = std::move(callback);
    }

    void setDisConnectedCallback(onDisConnectedCallback&& callback)
    {
        m_disConnectedCallback = std::move(callback);
    }


public:

    void onConnected(std::shared_ptr<TCPConnection>& spConn);
    void onDisConnected(std::shared_ptr<TCPConnection>& spConn);


    

private:
    //客户端的连接应该有Server来管理，Acceptor应该只管理监听
    void onAccept(int clientfd);


private:
    std::string                                                 m_ip;
    uint16_t                                                    m_port;

    ThreadPool                                                  m_threadPool;

    EventLoop                                                   m_baseEventLoop;
    Acceptor*                                                   m_acceptor;
    
    std::unordered_map<int, std::shared_ptr<TCPConnection>>     m_connections;

    onConnectedCallback                                         m_connectedCallback;
    onDisConnectedCallback                                      m_disConnectedCallback;

};

