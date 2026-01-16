#include "Timer.hpp"
#include <sstream>
#include <string>

float Engine::Timer::getSecondsElapsed()
{
    using namespace std::chrono;

    duration<float> result {high_resolution_clock::now() - start};
    return result.count();
}

std::string Engine::Timer::getPrettyTimeElapsed()
{
    using namespace std::chrono;

    nanoseconds ns = duration_cast<nanoseconds>(
        high_resolution_clock::now() - start
    );

    double count = ns.count();
    std::ostringstream out;

    if (count >= 1e9 * 3600) {
        out << std::llround(count / (1e9 * 3600)) << "hr";
    }
    else if (count >= 1e9 * 60) {
        out << std::llround(count / (1e9 * 60)) << "min";
    }
    else if (count >= 1e9) {
        out << std::llround(count / 1e9) << "sec";
    }
    else if (count >= 1e6) {
        out << std::llround(count / 1e6) << "ms";
    }
    else if (count >= 1e3) {
        out << std::llround(count / 1e3) << "µs";
    }
    else {
        out << static_cast<long long>(count) << "ns";
    }

    return out.str();
}
