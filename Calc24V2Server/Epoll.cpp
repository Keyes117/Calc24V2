#include "Epoll.h"

void Epoll::poll(int timeoutUs, std::vector<IEventDispatcher*> triggeredEventDispatchers)
{
    //使用epoll_wait

    struct  epoll_event events[1024];
    int timeoutMs, timeoutUs / 1000;
    int n = ::epoll_wait(m_epollfd, events, 1024, timeoutMs);

    bool enableRead = false;
    bool enableWrite = false;

    for (int i = 0; i < n; ++i)
    {
        if (events[i].events & EPOLLIN)
            enableRead = true;
        else
            enableRead = false;

        if (events[i].events & EPOLLOUT)
            enableWrite = true;
        else
            enableWrite = false;
            

        //events[0].data->ptr; // IEventDispachter* 
        IEventDispatcher* eventDispatcher = events[0].data->ptr;
        eventDispatcher->enableReadWrite(enableRead,enableWrite);
        triggeredEventDispatchers.push_back(eventDispatcher);
    }
}

void Epoll::registerReadEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent)
{
    //epoll_ctl

    struct epoll_event e;
    e.event |= EPOLLIN;
    e.data.ptr = eventDispatcher;
    //放入m_epollEvent 中

}

void Epoll::registerWriteEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent)
{

    struct epoll_event e;
    e.event |= EPOLLOUT;
    e.data.ptr = eventDispatcher;
}
