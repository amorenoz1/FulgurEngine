#pragma once

#include "core/FulgurCore.hpp"

#include <vector>

namespace Gfx {
class VulkanSynchronizationElements {
  private:
    std::vector<VkSemaphore> m_ImageAvailableSems;
    std::vector<VkSemaphore> m_RenderFinishedSems;
    std::vector<VkFence> m_InFlightFences;

  public:
    void CreateSynchronizationElements(VkDevice& device);
    std::vector<VkSemaphore>& GetImageAvailableSem();
    std::vector<VkSemaphore>& GetRenderFinishedSem();
    std::vector<VkFence>& GetInFlightFence();
    void CleanupSynchornizationElements(VkDevice& device);
};
} // namespace Gfx
