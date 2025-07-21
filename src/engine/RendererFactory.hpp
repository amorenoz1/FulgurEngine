#pragma once
#include "Renderer.hpp"
#include "core/FulgurCore.hpp"
#include <memory>

namespace Fulgur
{

    enum FGAPI RendererBackend : std::uint8_t
    {
        OPENGL = 0,
        VULKAN = 1,
    };

    class FGAPI RendererFactory
    {
      public:
        static auto GetRenderer(RendererBackend backend) -> std::unique_ptr<Renderer>;
    };
} // namespace Fulgur
