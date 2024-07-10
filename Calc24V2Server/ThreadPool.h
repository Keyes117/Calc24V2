/*
* œﬂ≥Ã≥ÿ¿‡
* zhkeyes 2024/7/10
*/

#pragma once
#include <cstdint>


#include <memory>
#include <thread>
#include <vector>


class ThreadPool final
{
public:
    ThreadPool() = default;
    ~ThreadPool() = default;

    void start(int32_t threadNum = 1);
    void stop();

private:
    void threadFunc();

private:
    bool                                                m_stop{ false };
    std::vector<std::shared_ptr<std::thread>>           m_threads;


private:
    ThreadPool(const ThreadPool& rhs) = delete;
    ThreadPool& operator=(const ThreadPool& rhs) = delete;

    ThreadPool(ThreadPool&& rhs) = delete;
    ThreadPool& operator=(ThreadPool&& rhs) = delete;

};

