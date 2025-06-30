#pragma once

#include "Window.hpp"
#include <cstdint>

namespace Fulgur {

class Application {
  private:
    Window m_Window;

    void MainLoop();

  protected:
  public:
    Application(const std::int32_t width, const std::int32_t height, const std::string& title);
    ~Application() = default;
    void Run();
};

} // namespace Fulgur
