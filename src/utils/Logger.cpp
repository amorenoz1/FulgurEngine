#include "Logger.hpp"
#include "Time.hpp"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

Utils::LoggingConfig                           Utils::Logger::m_Config;
std::ofstream                                  Utils::Logger::m_File;
std::chrono::high_resolution_clock::time_point Utils::Logger::m_StartTime;

void Utils::Logger::Init(const LoggingConfig &config)
{
    m_Config    = config;
    m_StartTime = std::chrono::high_resolution_clock::now();
    if (m_Config.output == LoggingOutput::FILE || m_Config.output == LoggingOutput::BOTH)
    {
        m_File.open(m_Config.logFilePath, std::ios::out | std::ios::trunc);
    }
}

void Utils::Logger::Shutdown()
{
    if (m_File.is_open())
    {
        m_File.close();
    }
}

void Utils::Logger::Log(LoggingPriority priority, const std::string &message, const char *file,
                        int line, const char *function)
{
    std::ostringstream oss;

    if (m_Config.timeStyle != LoggingTimeStyle::NOTIME)
    {
        oss << FormatExecutionTime(Utils::Time::GetTotalElapsedTime()) << " ";
    }

    oss << "[" << PriorityToString(priority) << "] ";

    if (m_Config.format == LoggingFormat::VERBOSE || m_Config.format == LoggingFormat::EXTENDED)
    {
        if ((file != nullptr) && line > 0)
        {
            oss << "[" << file << ":" << line << "] ";
        }
    }

    if (m_Config.format == LoggingFormat::EXTENDED && (function != nullptr))
    {
        oss << "[" << function << "] ";
    }

    oss << message;

    std::string fullMessage = oss.str();
    std::string colored     = (m_Config.colorOutput == LoggingColor::ENABLED)
                                  ? Colorize(priority, fullMessage)
                                  : fullMessage;

    if (m_Config.output == LoggingOutput::CONSOLE || m_Config.output == LoggingOutput::BOTH)
    {
        std::cout << colored << '\n';
    }

    if ((m_Config.output == LoggingOutput::FILE || m_Config.output == LoggingOutput::BOTH) &&
        m_File.is_open())
    {
        m_File << fullMessage << '\n';
    }
}

auto Utils::Logger::FormatExecutionTime(float seconds) -> std::string
{
    std::ostringstream out;
    if (seconds < 1.0F)
    {
        out << std::fixed << std::setprecision(0) << "[" << seconds * 1000.0F << "ms]";
    }
    else if (seconds < 60.0F)
    {
        out << std::fixed << std::setprecision(2) << "[" << seconds << "s]";
    }
    else if (seconds < 3600.0F)
    {
        int   minutes   = static_cast<int>(seconds) / 60;
        float remainSec = seconds - (minutes * 60);
        out << "[" << minutes << "m " << std::fixed << std::setprecision(1) << remainSec << "s]";
    }
    else
    {
        int   hours     = static_cast<int>(seconds) / 3600;
        int   minutes   = (static_cast<int>(seconds) % 3600) / 60;
        float remainSec = seconds - (hours * 3600 + minutes * 60);
        out << "[" << hours << "h " << minutes << "m " << std::fixed << std::setprecision(1)
            << remainSec << "s]";
    }
    return out.str();
}

auto Utils::Logger::PriorityToString(LoggingPriority p) -> std::string
{
    switch (p)
    {
        case LoggingPriority::TRACE:
            return "TRACE";
        case LoggingPriority::INFO:
            return "INFO";
        case LoggingPriority::WARNING:
            return "WARNING";
        case LoggingPriority::ERROR:
            return "ERROR";
    }
    return "UNKNOWN";
}

auto Utils::Logger::Colorize(LoggingPriority p, const std::string &msg) -> std::string
{
    const char *reset = "\033[0m";
    const char *color = "";

    switch (p)
    {
        case LoggingPriority::TRACE:
            color = "\033[36m";
            break;
        case LoggingPriority::INFO:
            color = "\033[32m";
            break;
        case LoggingPriority::WARNING:
            color = "\033[33m";
            break;
        case LoggingPriority::ERROR:
            color = "\033[31m";
            break;
    }

    return std::string(color) + msg + reset;
}
