#include "RendererFactory.hpp"
#include "engine/OpenGLRenderer.hpp"
#include "engine/VulkanRenderer.hpp"
#include <memory>

using std::make_unique;

auto Fulgur::RendererFactory::GetRenderer(RendererBackend backend)
    -> FGAPI std::unique_ptr<Renderer>
{
    switch (backend)
    {
        case OPENGL:
            return make_unique<OpenGLRenderer>();
            break;
        case VULKAN:
            return make_unique<VulkanRenderer>();
            break;
    }
}
