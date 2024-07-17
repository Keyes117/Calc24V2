#include "Epoll.h"

#include <sys/epoll.h>


#include <string.h>

#include "utils.h"
Epoll::Epoll()
{
    //创建一个fd
    m_epollfd = ::epoll_create1(EPOLL_CLOEXEC);
    if (m_epollfd < 0)
    {
        crash();
    }
}

Epoll::~Epoll()
{
}

void Epoll::poll(int timeoutUs, std::vector<IEventDispatcher*> triggeredEventDispatchers)
{
    //使用epoll_wait

    struct  epoll_event events[1024];
    int timeoutMs = timeoutUs / 1000;
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
        IEventDispatcher* eventDispatcher = static_cast<IEventDispatcher*>(events[0].data.ptr);
        eventDispatcher->enableReadWrite(enableRead, enableWrite);
        triggeredEventDispatchers.push_back(eventDispatcher);
    }
}

void Epoll::registerReadEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent)
{
    //想fdEventFlag中 查询fd是否有挂在IO事件

    int32_t eventFlag = 0;
    auto iter = m_fdEventFlags.find(fd);
    //如果没有过读事件
    if (iter == m_fdEventFlags.end())
    {
        eventFlag |= EPOLLIN;
        m_fdEventFlags[fd] = eventFlag;
    }
    else
    {
        eventFlag = iter->second;
        if (eventFlag & EPOLLIN)
            return;

        eventFlag |= EPOLLIN;
        m_fdEventFlags[fd] = eventFlag;
    }


    struct epoll_event event;
    memset(&event, 0, sizeof(event));
    event.events = eventFlag;


    event.data.ptr = eventDispatcher;
    if (::epoll_ctl(m_epollfd, EPOLL_CTL_ADD, fd, &event) < 0)
    {
        //TODO: 打印日志
        crash();
    }


    //放入m_epollEvent 中

}

void Epoll::registerWriteEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent)
{

    //想fdEventFlag中 查询fd是否有挂在IO事件

    int32_t eventFlag = 0;
    auto iter = m_fdEventFlags.find(fd);
    //如果没有过读事件
    if (iter == m_fdEventFlags.end())
    {
        eventFlag |= EPOLLOUT;
        m_fdEventFlags[fd] = eventFlag;
    }
    else
    {
        eventFlag = iter->second;
        if (eventFlag & EPOLLOUT)
            return;

        eventFlag |= EPOLLOUT;
        m_fdEventFlags[fd] = eventFlag;
    }

    struct epoll_event event;
    memset(&event, 0, sizeof(event));
    event.events = eventFlag;

    event.data.ptr = eventDispatcher;
    if (::epoll_ctl(m_epollfd, EPOLL_CTL_ADD, fd, &event) < 0)
    {
        //TODO: 打印日志
        crash();
    }
}

void Epoll::unregisterReadEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent)
{
    int32_t eventFlag = 0;
    int operation;
    auto iter = m_fdEventFlags.find(fd);
    //如果没有过读事件
    if (iter != m_fdEventFlags.end())
    {
        eventFlag = iter->second;
        if (eventFlag & EPOLLIN)
            return;

        eventFlag &= ~EPOLLIN;
        if (eventFlag == 0)
        {
            m_fdEventFlags.erase(iter);
            operation = EPOLL_CTL_DEL;
        }
        else
        {
            m_fdEventFlags[fd] = eventFlag;
            operation = EPOLL_CTL_MOD;
        }


    }

    struct epoll_event event;
    memset(&event, 0, sizeof(event));
    event.events = eventFlag;


    event.data.ptr = eventDispatcher;
    if (::epoll_ctl(m_epollfd, operation, fd, &event) < 0)
    {
        //TODO: 打印日志
        crash();
    }
}

void Epoll::unregisterWriteEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent)
{
    int32_t eventFlag = 0;
    int operation;
    auto iter = m_fdEventFlags.find(fd);
    //如果没有过读事件
    if (iter != m_fdEventFlags.end())
    {
        eventFlag = iter->second;
        if (eventFlag & EPOLLOUT)
            return;

        eventFlag &= ~EPOLLOUT;
        if (eventFlag == 0)
        {
            m_fdEventFlags.erase(iter);
            operation = EPOLL_CTL_DEL;
        }
        else
        {
            m_fdEventFlags[fd] = eventFlag;
            operation = EPOLL_CTL_MOD;
        }


    }

    struct epoll_event event;
    memset(&event, 0, sizeof(event));
    event.events = eventFlag;
    event.data.ptr = eventDispatcher;
    if (::epoll_ctl(m_epollfd, operation, fd, &event) < 0)
    {
        //TODO: 打印日志
        crash();
    }

}

void Epoll::unregisterAllEvent(int fd, IEventDispatcher* eventDispatcher)
{
    int32_t eventFlag = 0;
    auto iter = m_fdEventFlags.find(fd);
    //如果没有过读事件
    if (iter != m_fdEventFlags.end())
    {
        m_fdEventFlags.erase(iter);
    }

    struct epoll_event event;
    memset(&event, 0, sizeof(event));
    event.events = eventFlag;
    event.data.ptr = eventDispatcher;
    if (::epoll_ctl(m_epollfd, EPOLL_CTL_DEL, fd, &event) < 0)
    {
        //TODO: 打印日志
        crash();
    }
}
