#include "ThreadPool.h"

#include "EventLoop.h"

static constexpr int32_t MAX_THREAD_NUM = 20;
static constexpr int32_t DEFAULT_THREAD_NUM = 20;


void ThreadPool::start(int32_t threadNum /*=1*/)
{
    if (threadNum <= 0 || threadNum > MAX_THREAD_NUM)
        threadNum = DEFAULT_THREAD_NUM;

    for (int32_t i = 0; i < threadNum; ++i)
    {
        auto spEventLoop = std::make_shared<EventLoop>();
        spEventLoop->init();
        m_eventLoops.push_back(std::move(spEventLoop));
    }

    for (int32_t i = 0; i < threadNum; ++i)
    {
        //pthread_create
        auto spThread = std::make_shared<std::thread>(&ThreadPool::threadFunc, this, i);
        m_threads.push_back(std::move(spThread));
    }
}

void ThreadPool::stop()
{
    m_stop = true;

    size_t threadNum = m_threads.size();
    for (size_t i = 0; i < threadNum; ++i)
    {
        m_threads[i]->join();
    }

}

std::shared_ptr<EventLoop> ThreadPool::getNextEventLoop()
{

    auto spEventLoop = m_eventLoops[m_lastEventLoopNo];

    ++m_lastEventLoopNo;
    if (m_lastEventLoopNo >= m_eventLoops.size())
        m_lastEventLoopNo = 0;

    return spEventLoop;
}

void ThreadPool::threadFunc(size_t eventLoopIndex)
{
    while (!m_stop)
    {
        //实际的工作线程
        m_eventLoops[eventLoopIndex]->run();
    }
}
