/*
* zhkeyes 2024.03.14
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

    virtual void registerReadEvent(int fd,IEventDispatcher* eventDispatcher, bool readEvent) = 0;
    virtual void registerWriteEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent) = 0;


};