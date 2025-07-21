#pragma once
#include "Renderer.hpp"

namespace Fulgur
{
    class FGAPI OpenGLRenderer : public Renderer
    {
      private:
        int m_WindowWidth;
        int m_WindowHeight;

      public:
        void Init(GLFWwindow *window) override;
        void UseShader(Shader &shader) override;
        void SetVertexBuffer(IVertex *vertex) override;
        void SubmitVertexBuffer(const void *data, std::size_t size) override;
        void BeginFrame() override;
        void DrawRect(Vector2 pos, Vector2 dim, Vector3 color) override;
        void Flush() override;
        void EndFrame() override;
        void Shutdown() override;
    };

} // namespace Fulgur
