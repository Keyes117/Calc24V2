#include "Poll.h"

void Poll::poll(int timeoutUs, std::vector<IEventDispatcher*> triggeredEventDispatchers)
{
    //使用Poll 函数 
    poll(....);

    //拿到有事件的fd
    //遍历有事件的fd,通过m_eventDispachters 获取 IEventDispachter
}

void Poll::registerReadEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent)
{
    //往数组m_pollfd后面添加元素
    // 向m_pollfd结构中添加 pollfd；

}

void Poll::registerWriteEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent)
{
    //往数组m_pollfd后面添加元素
    //向m_pollfd 结构中添加 pollfd;
}
