#pragma once

#include "Timer.hpp"
#include <fstream>
#include <semaphore>
#include <thread>

namespace Engine 
{
    class Logger final
    {
        public:
          Logger(std::string_view log_file_name);
          Logger(const Logger &) = delete;
          Logger(Logger &&) = delete;
          Logger &operator=(const Logger &) = delete;
          Logger &operator=(Logger &&) = delete;
          ~Logger();

          void log(std::string_view priority, std::thread::id thread, std::string_view file, std::string_view function, int line, std::string_view message);

        private:
            Timer timer;
            std::binary_semaphore mutex;
            std::ofstream sink;
    };

    #define LOG_ERROR(logger, msg) \
        logger.log("ERROR", std::this_thread::get_id(), __builtin_FILE_NAME(),  __builtin_FUNCTION(), __builtin_LINE(), msg);

    #define LOG_WARN(logger, msg) \
        logger.log("WARN", std::this_thread::get_id(), __builtin_FILE_NAME(), __builtin_FUNCTION(), __builtin_LINE(), msg);
        
    #define LOG_INFO(logger, msg) \
        logger.log("INFO", std::this_thread::get_id(), __builtin_FILE_NAME(), __builtin_FUNCTION(), __builtin_LINE(), msg);

    #define LOG_TRACE(logger, msg) \
        logger.log("TRACE", std::this_thread::get_id(), __builtin_FILE_NAME(), __builtin_FUNCTION(), __builtin_LINE(), msg);
}
