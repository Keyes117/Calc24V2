#pragma once

#include "IOMultiplex.h"
#include <sys/types.h>
#include <sys/unistd.h>

#include <map>
#include <vector>

#define EVENT_FLAG_RAED     0x0001;
#define EVENT_FLAG_WRITE    0x0010;  //0x001 << 1£»

/*
*    int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
*/

class Epoll : public IOMultiplex
{
public:   

    Epoll();
    virtual ~Epoll();



public:

    virtual void poll(int timeoutUs, std::vector<IEventDispatcher*> triggeredEventDispatchers) override;


    virtual void registerReadEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent) override;
    virtual void registerWriteEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent) override;

    virtual void unregisterReadEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent) override;
    virtual void unregisterWriteEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent) override;
    virtual void unregisterAllEvent(int fd, IEventDispatcher* eventDispatcher) override;


private:
    int                     m_epollfd;
    //key=>fd , value=>eventFlags
    std::map<int, int32_t>  m_fdEventFlags;

private:
    Epoll(const Epoll& rhs) = delete;
    Epoll operator(const Epoll& rhs) = delete;

    Epoll(Epoll&& rhs) = delete;
    Epoll operator(Epoll&& rhs) = delete;

};

