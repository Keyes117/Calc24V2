#pragma once

#include "IOMultiplex.h"
#include <sys/types.h>
#include <sys/unistd.h>

#include <map>
#include <vector>


/*
*       int ppoll(struct pollfd *fds, nfds_t nfds,
               const struct timespec *tmo_p, const sigset_t *sigmask);

*/

class Poll : public IOMultiplex
{
public:

    Poll() = default;
    virtual ~Poll() = default;

    virtual void poll(int timeoutUs, std::vector<IEventDispatcher*> triggeredEventDispatchers) override;


    virtual void registerReadEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent) override;
    virtual void registerWriteEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent) override;

    virtual void unregisterReadEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent) override;
    virtual void unregisterWriteEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent) override;
    virtual void unregisterAllEvent(int fd, IEventDispatcher* eventDispatcher) override;

private:
    struct pollfd* m_pollfd;
    //key fd, value -
    std::map<int, IEventDispatcher*> m_eventDispachters;

};

