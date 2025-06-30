#include "Application.hpp"
#include "utils/Logger.hpp"
#include "utils/Time.hpp"

Fulgur::Application::Application(const std::int32_t width, const std::int32_t height,
                                 const std::string& title)
    : m_Window(width, height, title) {}

void Fulgur::Application::MainLoop() {
    while (!m_Window.WindowShouldClose()) {
        m_Window.PollEvents();
        m_Window.DrawFrame();
    }
    m_Window.Cleanup();
}

void Fulgur::Application::Run() { MainLoop(); }
