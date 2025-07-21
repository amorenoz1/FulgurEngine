#pragma once
#include "core/FulgurCore.hpp"
#include "engine/Shader.hpp"
#include "engine/VertexBuffer.hpp"
#include "utils/Math.hpp"
#include <vector>

namespace Fulgur
{
    class FGAPI Renderer
    {
      public:
        virtual ~Renderer()                            = default;
        Renderer()                                     = default;
        Renderer(Renderer &&)                          = delete;
        auto operator=(Renderer &&) -> Renderer &      = delete;
        Renderer(const Renderer &)                     = delete;
        auto operator=(const Renderer &) -> Renderer & = delete;

        virtual void Init(GLFWwindow *window)                               = 0;
        virtual void UseShader(Shader &shader)                              = 0;
        virtual void SetVertexBuffer(IVertex *vertex)                       = 0;
        virtual void SubmitVertexBuffer(const void *data, std::size_t size) = 0;
        virtual void BeginFrame()                                           = 0;
        virtual void DrawRect(Vector2 pos, Vector2 dim, Vector3 color)      = 0;
        virtual void Flush()                                                = 0;
        virtual void EndFrame()                                             = 0;
        virtual void Shutdown()                                             = 0;
    };

} // namespace Fulgur
