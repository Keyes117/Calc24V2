/*
* zhkeyes 2024.07.08
* IO���ú�����װ��Ľӿ���
*
*/

#pragma once
#include <vector>
#include "IEventDispatcher.h"

class IOMultiplex
{
public:
    IOMultiplex() = default;
    virtual ~IOMultiplex() = 0;

    virtual void poll(int timeoutUs, std::vector<IEventDispatcher*> triggeredEventDispatchers) = 0;

    //ע���д�¼�
    virtual void registerReadEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent) = 0;
    virtual void registerWriteEvent(int fd, IEventDispatcher* eventDispatcher, bool writeEvent) = 0;


    //�Ƴ���д�¼� 
    virtual void unregisterReadEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent) = 0;
    virtual void unregisterWriteEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent) = 0;
    virtual void unregisterAllEvent(int fd, IEventDispatcher* eventDispatcher) = 0;

};