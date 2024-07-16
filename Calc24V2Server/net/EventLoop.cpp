#include "EventLoop.h"

#include <sys/epoll.h>

#include <memory>

#include "Epoll.h"
#include "Poll.h"
#include "Select.h"


bool EventLoop::init(IOMultiplexType type /*= IOMultiplexType::IOMultiplexEpoll*/)
{
    if (type == IOMultiplexType::IOMultiplexSelect)
    {
        m_spIOMultiplex = std::make_unique<Select>();
    }
    else if (type == IOMultiplexType::IOMultiplexPoll)
    {
        m_spIOMultiplex = std::make_unique<Poll>();
    }
    else
    {
        m_spIOMultiplex = std::make_unique<Epoll>();
    }

    return m_epollfd != -1;
}

void EventLoop::run()
{
    //one thread one loop
    while (m_running)
    {
        //1. ���ʹ���ʱ���¼�

        //2. ʹ��select/poll/epoll ��IO���ú������һ��socket

  /*      struct epoll_event events[1024];
        int timeoutMs = 500;

        int n = ::epoll_wait(m_epollfd, events, 1024, timeoutMs);*/
        std::vector<IEventDispatcher*> eventDispatchers;
        m_spIOMultiplex->poll(500000, eventDispatchers);
        for (size_t i = 0; i < eventDispatchers.size(); ++i)
        {
            eventDispatchers[i]->onRead();
            eventDispatchers[i]->onWrite();
        }


        //3. �����д�¼�
        //�����¼�


        //4. ���û���fd���ƴ����Զ����¼�
    }

}

void EventLoop::registerReadEvents(int fd, IEventDispatcher* eventDispatcher ,bool readEvent)
{
    m_spIOMultiplex->registerReadEvent(fd, eventDispatcher, readEvent);
}

void EventLoop::registerWriteEvents(int fd, IEventDispatcher* eventDispatcher,bool writeEvent)
{
    m_spIOMultiplex->registerReadEvent(fd, eventDispatcher, writeEvent);
}

void EventLoop::unregisterReadEvents(int fd, IEventDispatcher* eventDispatcher, bool readEvent)
{
    m_spIOMultiplex->unregisterReadEvent(fd, eventDispatcher, readEvent);
}


void EventLoop::unregisterWriteEvents(int fd, IEventDispatcher* eventDispatcher, bool writeEvent)
{
    m_spIOMultiplex->unregisterReadEvent(fd, eventDispatcher, writeEvent);

}


void EventLoop::unregisterAllEvents(int fd, IEventDispatcher* eventDispatcher)
{
    m_spIOMultiplex->unregisterAllEvent(fd, eventDispatcher);
}

