#include "EventLoop.h"

#include <sys/epoll.h>

#include <memory>

#include "Epoll.h"
#include "Poll.h"
#include "Select.h"


EventLoop::EventLoop()
{
}

EventLoop::~EventLoop()
{
}

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

    m_running = true;

    return m_epollfd != -1;
}

void EventLoop::run()
{
    //one thread one loop
    while (m_running)
    {
        //1. 检测和处理定时器事件

        //2. 使用select/poll/epoll 等IO复用函数检测一组socket

        std::vector<IEventDispatcher*> eventDispatchers;
        m_spIOMultiplex->poll(500000, eventDispatchers);
        for (size_t i = 0; i < eventDispatchers.size(); ++i)
        {
            eventDispatchers[i]->onRead();
            eventDispatchers[i]->onWrite();
        }


        //3. 处理读写事件
        //遍历事件


        //4. 利用唤醒fd机制处理自定义事件
    }

}

void EventLoop::registerReadEvents(int fd, IEventDispatcher* eventDispatcher, bool readEvent)
{
    m_spIOMultiplex->registerReadEvent(fd, eventDispatcher, readEvent);
}

void EventLoop::registerWriteEvents(int fd, IEventDispatcher* eventDispatcher, bool writeEvent)
{
    m_spIOMultiplex->registerWriteEvent(fd, eventDispatcher, writeEvent);
}

void EventLoop::unregisterReadEvents(int fd, IEventDispatcher* eventDispatcher, bool readEvent)
{
    m_spIOMultiplex->unregisterReadEvent(fd, eventDispatcher, readEvent);
}


void EventLoop::unregisterWriteEvents(int fd, IEventDispatcher* eventDispatcher, bool writeEvent)
{
    m_spIOMultiplex->unregisterWriteEvent(fd, eventDispatcher, writeEvent);

}


void EventLoop::unregisterAllEvents(int fd, IEventDispatcher* eventDispatcher)
{
    m_spIOMultiplex->unregisterAllEvent(fd, eventDispatcher);
}

