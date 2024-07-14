/*
*  zhkeyes 2024/7/2
*/


#pragma once
#include <memory>

#include "IOMultiplex.h"
#include "IEventDispatcher.h"

enum class IOMultiplexType
{
    IOMultiplexSelect,
    IOMultiplexPoll,
    IOMultiplexEpoll
};

class EventLoop
{
public:
    EventLoop();
    ~EventLoop();


public:
    bool init(IOMultiplexType type = IOMultiplexType::IOMultiplexEpoll);

    void run();

    /*
    * registeFlag  true Îª×¢²á£¬ falseÎªÒÆ³ý×¢²á
    */
    void registerReadEvents(int fd, IEventDispatcher* eventDispatcher,bool registeFlag);

    void registerWriteEvents(int fd, IEventDispatcher* eventDispatcher, bool registeFlag);

private:
    bool            m_running{ true };
    int             m_epollfd;


    std::unique_ptr<IOMultiplex>    m_spIOMultiplex;
};

