/*
*  zhkeyes 2024/7/2
*/


#pragma once

class EventLoop
{
public:
    EventLoop();
    ~EventLoop();


public:
    bool init();

    void run();

private:
    bool            m_running{ true };
    int             m_epollfd;

};

