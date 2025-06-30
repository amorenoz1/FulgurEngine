#pragma once

#include "VulkanDevice.hpp"
#include "core/FulgurCore.hpp"

namespace Gfx {
class VulkanQueue {
  private:
    VkQueue m_GraphicsQueue;
    VkQueue m_PresentQueue;

  public:
    VulkanQueue() = default;
    ~VulkanQueue() = default;

    VulkanQueue(const VulkanQueue&) = delete;
    VulkanQueue& operator=(const VulkanQueue&) = delete;

    void RetrieveQueues(VkDevice& device, QueueFamiliesIndices indices);
    VkQueue& GetPresentQueue();
    VkQueue& GetGraphicsQueue();
    void Cleanup();
};
}; // namespace Gfx
