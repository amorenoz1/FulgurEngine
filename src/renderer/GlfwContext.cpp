#include "GlfwContext.hpp"
#include "utils/FulgurUtils.hpp"
#include "utils/Logger.hpp"

void Fulgur::GlfwContext::InitGlfwContext(std::int32_t width, std::int32_t height,
                                          std::string& title) {
    m_Width = width;
    m_Height = height;
    m_Title = title;

    std::int32_t glfwInitRes = glfwInit();

    Utils::Assert(glfwInitRes == GLFW_TRUE, "Glfw initialization failed!");

    LOG_INFO("Glfw initalization was successful!");

    glfwWindowHint(GLFW_NO_API, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);

    Utils::Assert(m_Window != nullptr, "Window creation failed!");

    LOG_INFO("Window creation was successful!");
}

GLFWwindow* Fulgur::GlfwContext::GetWindowPtr() { return m_Window; }

std::int32_t Fulgur::GlfwContext::GetHeight() { return m_Height; }

std::int32_t Fulgur::GlfwContext::GetWidth() { return m_Width; }

std::string& Fulgur::GlfwContext::GetTitle() { return m_Title; }

void Fulgur::GlfwContext::CleanupGlfwContext() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}
