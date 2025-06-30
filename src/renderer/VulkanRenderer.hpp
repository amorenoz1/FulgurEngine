#pragma once

#include "core/FulgurCore.hpp"
#include "gfx/Shader.hpp"
#include "gfx/VulkanCommandBuffer.hpp"
#include "gfx/VulkanCommandPool.hpp"
#include "gfx/VulkanContext.hpp"
#include "gfx/VulkanDevice.hpp"
#include "gfx/VulkanFrameBuffer.hpp"
#include "gfx/VulkanGraphicsPipeline.hpp"
#include "gfx/VulkanQueue.hpp"
#include "gfx/VulkanSwapChain.hpp"
#include "gfx/VulkanSynchronization.hpp"
#include "utils/Math.hpp"
#include <string>

namespace Fulgur {
class Renderer {
  private:
    GLFWwindow* m_Window;
    Gfx::VulkanContext m_Context;
    Gfx::VulkanDevice m_Device;
    Gfx::VulkanSwapChain m_Swapchain;
    Gfx::VulkanFrameBuffer m_Framebuffer;
    Gfx::VulkanGraphicsPipeline m_GraphicsPipeline;
    Gfx::VulkanQueue m_Queues;
    Gfx::VulkanCommandPool m_CommandPool;
    Gfx::VulkanCommandBuffer m_CommandBuffer;
    Gfx::VulkanSynchronizationElements m_SyncElements;

    std::uint32_t m_CurrentFrame;

    void RecreateSwapchain();

  public:
    void Initialize(GLFWwindow* window);
    void Clear(Vector4 color);
    void UseShader(Gfx::Shader shader);
    void DrawRect(Vector2 position, Vector2 dimension, Vector4 color);
    void DrawCircle(Vector2 position, Vector2 dimension, Vector4 color);
    void DrawTriangle(Vector2 position, Vector2 dimension, Vector4 color);
    void Present();
    void Shutdown();
};
} // namespace Fulgur
