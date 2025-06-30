#pragma once

#include "core/FulgurCore.hpp"

#include <vector>

namespace Gfx {
class VulkanFrameBuffer {
  private:
    std::vector<VkFramebuffer> m_SwapChainFramebuffer;

  public:
    void CreateFrameBuffer(VkDevice& device, std::vector<VkImageView>& imageViews,
                           VkRenderPass& renderPass, VkExtent2D& extent);
    std::vector<VkFramebuffer>& GetSwapChainFramebuffer();
    void CleanupFrameBuffer(VkDevice& device);
};
} // namespace Gfx
