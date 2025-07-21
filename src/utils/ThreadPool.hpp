#pragma once
#include "core/FulgurCore.hpp"
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace Utils
{
    class ThreadPool
    {
        std::queue<std::function<void()>> m_Tasks;
        std::vector<std::thread>          m_Workers;

        std::mutex              m_BufferMutex;
        std::condition_variable m_ConditionVariable;
        std::atomic<bool>       m_Running;

        void ThreadLoop();

      public:
        ThreadPool(std::size_t threads);
        ~ThreadPool();

        void EnqueueJob(const std::function<void()> &job);
    };
} // namespace Utils
