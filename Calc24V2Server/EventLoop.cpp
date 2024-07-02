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
        //1. ���ʹ���ʱ���¼�

        //2. ʹ��select/poll/epoll ��IO���ú������һ��socket

        struct epoll_event events[1024];
        int timeoutMs = 500;

        int n = ::epoll_wait(m_epollfd, events, 1024, timeoutMs);

        //3. �����д�¼�
        //�����¼�


        //4. ���û���fd���ƴ����Զ����¼�
    }

}
