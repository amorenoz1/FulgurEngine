#include "Time.hpp"
#include <chrono>
#include <ctime>
#include <iomanip> // for std::put_time
#include <sstream>

std::chrono::high_resolution_clock::time_point Utils::Time::m_InitialTime;
std::chrono::high_resolution_clock::time_point Utils::Time::m_FrameTimeStart;
std::chrono::high_resolution_clock::time_point Utils::Time::m_FrameTimeEnd;

auto Utils::Time::GetFrameTime() -> std::float_t
{
    std::chrono::duration<float> delta = m_FrameTimeEnd - m_FrameTimeStart;
    return delta.count();
}

auto Utils::Time::GetTotalElapsedTime() -> std::float_t
{
    std::chrono::duration<float> delta = std::chrono::high_resolution_clock::now() - m_InitialTime;
    return delta.count();
}

auto Utils::Time::GetTimestamp() -> std::string
{
    auto        now = std::chrono::system_clock::now();
    std::time_t raw = std::chrono::system_clock::to_time_t(now);

    std::stringstream stream;
    std::tm          *timeinfo = std::localtime(&raw);

    if (timeinfo != nullptr)
    {
        stream << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S");
    }
    else
    {
        stream << "Invalid Time";
    }

    return stream.str();
}

auto Utils::Time::GetCurrentTime() -> std::time_t
{
    return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

void Utils::Time::Init()
{
    m_InitialTime = std::chrono::high_resolution_clock::now();
}

void Utils::Time::Shutdown()
{
    m_InitialTime    = {};
    m_FrameTimeStart = {};
    m_FrameTimeEnd   = {};
}

void Utils::Time::SetFrameTimeStart()
{
    m_FrameTimeStart = std::chrono::high_resolution_clock::now();
}

void Utils::Time::SetFrameTimeEnd()
{
    m_FrameTimeEnd = std::chrono::high_resolution_clock::now();
}
