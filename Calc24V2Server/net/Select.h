#pragma once


#include "IOMultiplex.h"
#include <sys/types.h>
#include <sys/unistd.h>

#include <vector>

/*
*   int select(int nfds, fd_set *readfds, fd_set *writefds,
                  fd_set *exceptfds, struct timeval *timeout);
*/

class Select : public IOMultiplex
{
public:
    virtual void poll(int timeoutUs, std::vector<IEventDispatcher*> triggeredEventDispatchers) override;


    virtual void registerReadEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent) override;
    virtual void registerWriteEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent) override;

private:
    int                     m_maxfd;
    fd_set                  m_readfds;
    fd_set                  m_writefds;
    fd_set                  m_exceptfds;
    fd_set                  m_timeout;

};
