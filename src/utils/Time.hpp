#pragma once
#include "core/FulgurCore.hpp"
#include <chrono>
#include <cmath>
#include <ctime>
#include <string>

namespace Utils
{
    class Time
    {
      private:
        static std::chrono::high_resolution_clock::time_point m_InitialTime;
        static std::chrono::high_resolution_clock::time_point m_FrameTimeStart;
        static std::chrono::high_resolution_clock::time_point m_FrameTimeEnd;

      public:
        static void Init();
        static void SetFrameTimeStart();
        static void SetFrameTimeEnd();
        static void Shutdown();

        static auto GetCurrentTime() -> std::time_t;
        static auto GetTimestamp() -> std::string;
        static auto GetFrameTime() -> std::float_t;
        static auto GetTotalElapsedTime() -> std::float_t;
    };
} // namespace Utils
