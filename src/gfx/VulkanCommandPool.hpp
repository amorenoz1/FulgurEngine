#pragma once
#include "core/FulgurCore.hpp"
#include "gfx/VulkanDevice.hpp"

namespace Gfx {
class VulkanCommandPool {
  private:
    VkCommandPool m_CommandPool;

  public:
    void CreateCommandPool(VkDevice& device, QueueFamiliesIndices indices);
    VkCommandPool& GetCommandPool();
    void CleanupCommandPool(VkDevice& device);
};
} // namespace Gfx
