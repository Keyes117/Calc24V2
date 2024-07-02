/*
* zhkeyes 2024/7/2
*/
#pragma once

class IEventDispatcher
{
public:
    IEventDispatcher();
    virtual ~IEventDispatcher() = 0;


    virtual void onRead() = 0;
    virtual void onWrite() = 0;
};