#pragma once

#include "core/FulgurCore.hpp"
#include <string>

namespace Fulgur {

class GlfwContext {
  private:
    GLFWwindow* m_Window;
    std::int32_t m_Width;
    std::int32_t m_Height;
    std::string m_Title;

  public:
    void InitGlfwContext(std::int32_t width, std::int32_t height, std::string& title);
    GLFWwindow* GetWindowPtr();
    std::int32_t GetHeight();
    std::int32_t GetWidth();
    std::string& GetTitle();
    void CleanupGlfwContext();
};

}; // namespace Fulgur
