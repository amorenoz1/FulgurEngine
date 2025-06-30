#pragma once

#include "core/FulgurCore.hpp"
#include <vector>

namespace Gfx {
class VulkanCommandBuffer {
  private:
    std::vector<VkCommandBuffer> m_CommandBuffers;

  public:
    void CreateCommandBuffer(VkDevice& device, VkCommandPool& commandPool);
    std::vector<VkCommandBuffer>& GetCommandBuffer();
    void CleanupCommandBuffer(VkDevice& device, VkCommandPool& commandPool);
};
} // namespace Gfx
