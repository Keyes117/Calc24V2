#include "Poll.h"

void Poll::poll(int timeoutUs, std::vector<IEventDispatcher*> triggeredEventDispatchers)
{
    //ʹ��Poll ���� 
    poll(....);

    //�õ����¼���fd
    //�������¼���fd,ͨ��m_eventDispachters ��ȡ IEventDispachter
}

void Poll::registerReadEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent)
{
    //������m_pollfd�������Ԫ��
    // ��m_pollfd�ṹ����� pollfd��

}

void Poll::registerWriteEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent)
{
    //������m_pollfd�������Ԫ��
    //��m_pollfd �ṹ����� pollfd;
}
