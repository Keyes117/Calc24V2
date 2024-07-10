#include "ThreadPool.h"

#include "EventLoop.h"

static constexpr int32_t MAX_THREAD_NUM = 20;
static constexpr int32_t DEFAULT_THREAD_NUM = 20;


void ThreadPool::start(int32_t threadNum /*=1*/)
{
    if (threadNum <= 0 || threadNum > MAX_THREAD_NUM)
        threadNum = DEFAULT_THREAD_NUM;

    for (size_t i = 0; i < threadNum; ++i)
    {
        //pthread_create
        auto spThread = std::make_shared<std::thread>(threadFunc);
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

void ThreadPool::threadFunc()
{
    EventLoop eventLoop;
    eventLoop.init();

    while (!m_stop)
    {
        //实际的工作线程
        eventLoop.run();
    }
}
