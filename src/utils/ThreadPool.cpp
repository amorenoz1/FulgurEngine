#include "ThreadPool.hpp"

Utils::ThreadPool::ThreadPool(std::size_t threads)
{
    m_Running = true;
    for (std::size_t i = 0; i < threads; i++)
    {
        m_Workers.emplace_back([this] { ThreadLoop(); });
    }
}

void Utils::ThreadPool::ThreadLoop()
{
    while (true)
    {
        std::function<void()> Job;

        {
            std::unique_lock<std::mutex> Lock(m_BufferMutex);
            m_ConditionVariable.wait(Lock, [this] { return !m_Tasks.empty() || !m_Running; });

            if (!m_Running && m_Tasks.empty())
            {
                return;
            }

            Job = std::move(m_Tasks.front());
            m_Tasks.pop();
        }

        Job();
    }
}

void Utils::ThreadPool::EnqueueJob(const std::function<void()> &job)
{
    {
        std::unique_lock<std::mutex> Lock(m_BufferMutex);
        m_Tasks.push(job);
    }
    m_ConditionVariable.notify_one();
}

Utils::ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(m_BufferMutex);
        m_Running = false;
    }

    m_ConditionVariable.notify_all();

    for (std::thread &t : m_Workers)
    {
        t.join();
    }
}
