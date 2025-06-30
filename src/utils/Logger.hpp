#pragma once

#include <chrono>
#include <fstream>
#include <string>

namespace Utils {

enum class LoggingPriority : uint8_t { TRACE, INFO, WARNING, ERROR };

enum class LoggingTimeStyle : uint8_t { EXECUTION, CURRENT, NOTIME };

enum class LoggingOutput : uint8_t { CONSOLE, FILE, BOTH };

enum class LoggingColor : uint8_t { ENABLED, DISABLED };

enum class LoggingFormat : uint8_t { DEFAULT, VERBOSE, EXTENDED };

struct LoggingConfig {
    LoggingTimeStyle timeStyle = LoggingTimeStyle::CURRENT;
    LoggingOutput output = LoggingOutput::CONSOLE;
    LoggingColor colorOutput = LoggingColor::ENABLED;
    LoggingFormat format = LoggingFormat::DEFAULT;
    std::string logFilePath = "engine.log";
};

class Logger {
  public:
    static void Init(const LoggingConfig& config);
    static void Shutdown();
    static void Log(LoggingPriority priority, const std::string& message,
                    const char* file = nullptr, int line = 0, const char* function = nullptr);

  private:
    static LoggingConfig m_Config;
    static std::ofstream m_File;
    static std::chrono::high_resolution_clock::time_point m_StartTime;

    static std::string FormatExecutionTime(float seconds);
    static std::string PriorityToString(LoggingPriority p);
    static std::string Colorize(LoggingPriority p, const std::string& msg);
};

} // namespace Utils

#define LOG_TRACE(msg)                                                                             \
    Utils::Logger::Log(Utils::LoggingPriority::TRACE, msg, __FILE__, __LINE__, __func__)
#define LOG_INFO(msg)                                                                              \
    Utils::Logger::Log(Utils::LoggingPriority::INFO, msg, __FILE__, __LINE__, __func__)
#define LOG_WARNING(msg)                                                                           \
    Utils::Logger::Log(Utils::LoggingPriority::WARNING, msg, __FILE__, __LINE__, __func__)
#define LOG_ERROR(msg)                                                                             \
    Utils::Logger::Log(Utils::LoggingPriority::ERROR, msg, __FILE__, __LINE__, __func__)
