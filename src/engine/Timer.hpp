#pragma once

#include <chrono>
#include <string>

namespace Engine 
{
    class Timer final 
    {
        public:
            Timer() = default;
            Timer(const Timer &) = delete;
            Timer(Timer &&) = delete;
            Timer &operator=(const Timer &) = delete;
            Timer &operator=(Timer &&) = delete;
            ~Timer() = default;

            float getSecondsElapsed();
            std::string getPrettyTimeElapsed();

        private:
            std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
    };
}
