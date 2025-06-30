#pragma once

#include "core/FulgurCore.hpp"
#include <vector>

namespace Gfx {
class VulkanGraphicsPipeline {
  private:
    VkPipelineLayout m_PipelineLayout;
    VkRenderPass m_RenderPass;
    VkPipeline m_GraphicsPipeline;

    VkShaderModule CreateShaderModule(VkDevice& device, const std::vector<char>& shaderBin);

    void CreateRenderPass(VkDevice& device, VkFormat& format);

  public:
    void CreateGraphicsPipeline(VkDevice& device, VkExtent2D& extent, VkFormat& format);
    VkPipelineLayout& GetPipelineLayout();
    VkRenderPass& GetRenderPass();
    VkPipeline& GetGraphicsPipeline();
    void CleanupGraphicsPipeline(VkDevice& device);
};
} // namespace Gfx
