#include "Select.h"


void Select::poll(int timeoutUs, std::vector<IEventDispatcher*> triggeredEventDispatchers)
{
    /* struct timeval tv;
     tv.tv_sec = timeoutUs / 1000000;
     tv.tv_usec = timeoutUs - timeoutUs / 1000000 * 1000000;

     int n =::select(m_maxfd + 1, &m_readfds, &m_writefds ,nullptr, );
     if (n <= 0)
         return;*/

         //TODO: ����m_readfds, ����FD_ISSET�ж���Щsocket �ɶ�
         //fd => I


         //TODO: ����m_writefds, ����FD_ISSET�ж���Щsocket ��д

}

void Select::registerReadEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent)
{
    /*  if (m_max < fd)
          m_maxfd = fd;

      FD_SET(fd, &m_readfds);*/

}

void Select::registerWriteEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent)
{
}


void Select::unregisterReadEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent)
{
}

void Select::unregisterWriteEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent)
{
}

void Select::unregisterAllEvent(int fd, IEventDispatcher* eventDispatcher)
{
}
