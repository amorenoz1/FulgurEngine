#include "Logger.hpp"
#include <iostream>
#include <sstream>

Engine::Logger::Logger(std::string_view log_file_name) : timer{}, mutex{1}, sink{}
{ 
    if (!log_file_name.empty())
    {
        try 
        {
            sink.open(log_file_name);
        } catch(const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}

Engine::Logger::~Logger()
{
    if (sink.is_open())
    {
        sink.close();
    }
}

void Engine::Logger::log(std::string_view priority, std::thread::id thread, std::string_view file,  std::string_view function, int line, std::string_view message)
{
    std::ostringstream log_result;
    
    log_result << "[ " << timer.getPrettyTimeElapsed() << " ] ";
    log_result << "[ " << priority << " ] ";
    log_result << "[ " << thread << " ] ";
    log_result << "[ " << file << " ] ";
    log_result << "[ " << function << " ] ";
    log_result << "[ " << line << " ] ";
    log_result << message << "\n";

    mutex.acquire();
    std::cout << log_result.str();

    if(sink.is_open())
    {
        sink << log_result.str();
    }
    mutex.release();
}
