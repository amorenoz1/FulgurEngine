#include "OpenGLRenderer.hpp"
#include "utils/FulgurUtils.hpp"

void Fulgur::OpenGLRenderer::Init(GLFWwindow *window)
{
    std::int32_t gladInitRes = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    Utils::Assert(static_cast<bool>(gladInitRes), "Unable to load opengl with glad!");

    glfwGetFramebufferSize(window, &m_WindowWidth, &m_WindowHeight);
}
