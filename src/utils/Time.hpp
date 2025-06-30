#pragma once

#include <chrono>
#include <cmath>
#include <ctime>
#include <string>

namespace Utils {
class Time {
  private:
    static std::chrono::high_resolution_clock::time_point m_InitialTime;
    static std::chrono::high_resolution_clock::time_point m_FrameTimeStart;
    static std::chrono::high_resolution_clock::time_point m_FrameTimeEnd;

  public:
    static void Init();
    static void SetFrameTimeStart();
    static void SetFrameTimeEnd();
    static void Shutdown();

    static std::time_t GetCurrentTime();
    static std::string GetTimestamp();
    static std::float_t GetFrameTime();
    static std::float_t GetTotalElapsedTime();
};
} // namespace Utils
