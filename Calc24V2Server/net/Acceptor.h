/*
* 2024.07.10
* ZhKeyes Acceptor ¿‡
*/
#pragma once

#include "EventLoop.h"
#include "IEventDispatcher.h"

#include <functional>
#include <string>

using AcceptCallback = std::function<void(int clientfd)>;

class Acceptor final : public IEventDispatcher
{
public:
    Acceptor(EventLoop* pEventLoop) ;
    ~Acceptor();

    //void onAccept(int clientfd);

    virtual void onRead() override;

    bool startListen(const std::string& ip="", uint16_t port=8888);

    void setAcceptCallback(AcceptCallback&& callback)
    {
        m_acceptCallback = std::move(callback);
    }


private:
    int                 m_listenfd;
    EventLoop*          m_pEventLoop;

    AcceptCallback      m_acceptCallback;
private:
    virtual void onWrite() override {}

    virtual void onClose() override {}

    virtual void enableReadWrite(bool read, bool write) override {}

};

