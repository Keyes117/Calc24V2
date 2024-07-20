/*
* zhkeyes 2024/7/2
*/
#pragma once

class IEventDispatcher
{
public:
    IEventDispatcher() = default;
    virtual ~IEventDispatcher() = default;

    virtual void onRead() = 0;
    virtual void onWrite() = 0;

    virtual void onClose() = 0;

    virtual void enableReadWrite(bool read, bool write) = 0;



};