#include "VulkanRenderer.hpp"
#include <cstdint>
#include <vulkan/vulkan_core.h>

void Fulgur::Renderer::Initialize(GLFWwindow* window) {
    m_Window = window;

    m_Context.CreateContext();

    auto& vkInst = m_Context.GetVulkanInstance();

    m_Device.CreateDevice(vkInst, window);

    auto& device = m_Device.GetLogicalDevice();
    auto& surface = m_Device.GetSurface();
    auto indices = m_Device.FindQueueFamilies();
    auto details = m_Device.QuerySwapChainSupport();

    m_Swapchain.CreateSwapChain(device, surface, indices, details, window);

    auto& extent = m_Swapchain.GetExtent2D();
    auto& surfaceFormat = m_Swapchain.GetSurfaceFormat();
    auto& imageViews = m_Swapchain.GetImageViews();

    m_GraphicsPipeline.CreateGraphicsPipeline(device, extent, surfaceFormat.format);

    auto& renderPass = m_GraphicsPipeline.GetRenderPass();

    m_Framebuffer.CreateFrameBuffer(device, imageViews, renderPass, extent);

    auto& swapChainFramebuffers = m_Framebuffer.GetSwapChainFramebuffer();

    m_CommandPool.CreateCommandPool(device, indices);

    auto& commandPool = m_CommandPool.GetCommandPool();

    m_CommandBuffer.CreateCommandBuffer(device, commandPool);

    m_SyncElements.CleanupSynchornizationElements(device);

    m_Queues.RetrieveQueues(device, indices)
}

void Fulgur::Renderer::RecreateSwapchain() {
    auto& device = m_Device.GetLogicalDevice();
    auto& surface = m_Device.GetSurface();
    auto indices = m_Device.FindQueueFamilies();
    auto details = m_Device.QuerySwapChainSupport();

    vkDeviceWaitIdle(device);

    m_Framebuffer.CleanupFrameBuffer(device);
    m_Swapchain.CleanupSwapChain(device);

    m_Swapchain.CreateSwapChain(device, surface, indices, details, m_Window);

    auto& extent = m_Swapchain.GetExtent2D();
    auto& surfaceFormat = m_Swapchain.GetSurfaceFormat();
    auto& imageViews = m_Swapchain.GetImageViews();
    auto& renderPass = m_GraphicsPipeline.GetRenderPass();

    m_Framebuffer.CreateFrameBuffer(device, imageViews, renderPass, extent);
}

void Fulgur::Renderer::Clear(Vector4 color) {}

void Fulgur::Renderer::UseShader(Gfx::Shader shader) {}

void Fulgur::Renderer::DrawRect(Vector2 position, Vector2 dimension, Vector4 color) {}

void Fulgur::Renderer::DrawCircle(Vector2 position, Vector2 dimension, Vector4 color) {}

void Fulgur::Renderer::DrawTriangle(Vector2 position, Vector2 dimension, Vector4 color) {}

void Fulgur::Renderer::Present() {
    VkDevice device = m_Device.GetLogicalDevice();
    auto& inFlightFences = m_SyncElements.GetInFlightFence();
    auto& imageAvailableSemaphores = m_SyncElements.GetImageAvailableSem();
    auto& renderFinishedSemaphores = m_SyncElements.GetRenderFinishedSem();
    auto& commandBuffers = m_CommandBuffer.GetCommandBuffer();
    auto graphicsQueue = m_Queues.GetGraphicsQueue();
    auto presentQueue = m_Queues.GetPresentQueue();

    std::uint32_t imageIndex;
    VkResult getImageIndexRes = vkAcquireNextImageKHR(
        device, m_Swapchain.GetSwapChain(), UINT64_MAX, imageAvailableSemaphores[m_CurrentFrame],
        VK_NULL_HANDLE, &imageIndex);
}

void Fulgur::Renderer::Shutdown() {}
