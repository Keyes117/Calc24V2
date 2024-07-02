#include "EventLoop.h"

#include <sys/epoll.h>

bool EventLoop::init()
{
    m_epollfd = ::epoll_create(1);

    return m_epollfd != -1;
}

void EventLoop::run()
{
    while (m_running)
    {
        //1. 检测和处理定时器事件

        //2. 使用select/poll/epoll 等IO复用函数检测一组socket

        struct epoll_event events[1024];
        int timeoutMs = 500;

        int n = ::epoll_wait(m_epollfd, events, 1024, timeoutMs);

        //3. 处理读写事件
        //遍历事件


        //4. 利用唤醒fd机制处理自定义事件
    }

}
