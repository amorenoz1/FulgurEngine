#include "src/engine/Application.hpp"
#include "utils/Logger.hpp"
#include "utils/Time.hpp"

static Utils::LoggingConfig config {
    .timeStyle = Utils::LoggingTimeStyle::EXECUTION,
    .output = Utils::LoggingOutput::CONSOLE,
    .colorOutput = Utils::LoggingColor::ENABLED,
    .format = Utils::LoggingFormat::DEFAULT,
    .logFilePath = ""
};
int main () {
    Utils::Time::Init();
    Utils::Logger::Init(config);
    Fulgur::Application app(800, 600, "Test");
    app.Run();
    Utils::Time::Shutdown();
}
