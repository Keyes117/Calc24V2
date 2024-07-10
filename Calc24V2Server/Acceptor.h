/*
* 2024.07.10
* ZhKeyes Acceptor ¿‡
*/
#pragma once

#include "EventLoop.h"
#include "IEventDispatcher.h"


class Acceptor final : public IEventDispatcher
{
public:
    Acceptor(EventLoop* pEventLoop) ;
    ~Acceptor();

    virtual void onRead() override;

    bool startListen(const std::string& ip, uint16_t port);


private:
    int                 m_listenfd;
    EventLoop*          m_pEventLoop;

private:
    virtual void onWrite() override {}

    virtual void onClose() override {}

    virtual void enableReadWrite(bool read, bool write) override {}

};

