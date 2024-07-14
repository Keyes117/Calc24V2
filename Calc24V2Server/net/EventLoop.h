/*
*  zhkeyes 2024/7/2
*/


#pragma once

#include "IOMultiplex.h"

class EventLoop
{
public:
    EventLoop();
    ~EventLoop();


public:
    bool init();

    void run();

    /*
    * registeFlag  true Ϊע�ᣬ falseΪ�Ƴ�ע��
    */
    void registerReadEvents(int fd, bool registeFlag);

    void registerWriteEvents(int fd, bool registeFlag);

private:
    bool            m_running{ true };
    int             m_epollfd;


    IOMultiplex*    m_pIOMultiplex;
};

