#include "VulkanFrameBuffer.hpp"
#include "utils/FulgurUtils.hpp"
#include "utils/Logger.hpp"
#include <vulkan/vulkan_core.h>

void Gfx::VulkanFrameBuffer::CreateFrameBuffer(VkDevice& device,
                                               std::vector<VkImageView>& imageViews,
                                               VkRenderPass& renderPass, VkExtent2D& extent) {
    m_SwapChainFramebuffer.resize(imageViews.size());

    for (std::size_t i = 0; i < imageViews.size(); i++) {
        VkImageView attachments[] = {imageViews[i]};

        VkFramebufferCreateInfo createInfo{.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
                                           .pNext = nullptr,
                                           .flags = 0,
                                           .renderPass = renderPass,
                                           .attachmentCount = 1,
                                           .pAttachments = attachments,
                                           .width = extent.width,
                                           .height = extent.height,
                                           .layers = 1};

        VkResult framebufferCreationRes =
            vkCreateFramebuffer(device, &createInfo, nullptr, &m_SwapChainFramebuffer[i]);

        Utils::Assert(framebufferCreationRes == VK_SUCCESS, "VkFramebuffer creation failed!");

        LOG_INFO("VkFramebuffer creation was successful!");
    }
}

std::vector<VkFramebuffer>& Gfx::VulkanFrameBuffer::GetSwapChainFramebuffer() {
    return m_SwapChainFramebuffer;
}

void Gfx::VulkanFrameBuffer::CleanupFrameBuffer(VkDevice& device) {
    for (auto& framebuffer : m_SwapChainFramebuffer) {
        vkDestroyFramebuffer(device, framebuffer, nullptr);
    }
}
