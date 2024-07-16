/*
* zhkeyes 2024.07.08
* IO复用函数包装类的接口类
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

    //注册读写事件
    virtual void registerReadEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent) = 0;
    virtual void registerWriteEvent(int fd, IEventDispatcher* eventDispatcher, bool writeEvent) = 0;


    //移除读写事件 
    virtual void unregisterReadEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent) = 0;
    virtual void unregisterWriteEvent(int fd, IEventDispatcher* eventDispatcher, bool readEvent) = 0;
    virtual void unregisterAllEvent(int fd, IEventDispatcher* eventDispatcher) = 0;

};