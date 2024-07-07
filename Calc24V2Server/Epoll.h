#pragma once

#include "IOMultiplex.h"
#include <sys/types.h>
#include <sys/unistd.h>

#include <vector>

/*
*    int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
*/

class Epoll : public IOMultiplex
{
public:   

    virtual void poll(int timeoutUs, std::vector<IEventDispatcher*> triggeredEventDispatchers) override;


    virtual void registerReadEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent) override;
    virtual void registerWriteEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent) override;

private:
    struct pollfd m_pollfd;


};

