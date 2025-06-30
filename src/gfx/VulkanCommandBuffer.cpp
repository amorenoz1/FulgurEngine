#include "VulkanCommandBuffer.hpp"
#include "utils/FulgurUtils.hpp"
#include "utils/Logger.hpp"
#include <vulkan/vulkan_core.h>

void Gfx::VulkanCommandBuffer::CreateCommandBuffer(VkDevice& device, VkCommandPool& commandPool) {
    m_CommandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

    VkCommandBufferAllocateInfo allocateInfo{
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .pNext = nullptr,
        .commandPool = commandPool,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount = static_cast<std::uint32_t>(m_CommandBuffers.size())};

    VkResult commandBufferAllocateRes =
        vkAllocateCommandBuffers(device, &allocateInfo, m_CommandBuffers.data());

    Utils::Assert(commandBufferAllocateRes == VK_SUCCESS, "VkCommandBuffer allocation failed!");

    LOG_INFO("VkCommandBuffer allocation was successful!");
}

std::vector<VkCommandBuffer>& Gfx::VulkanCommandBuffer::GetCommandBuffer() {
    return m_CommandBuffers;
}

void Gfx::VulkanCommandBuffer::CleanupCommandBuffer(VkDevice& device, VkCommandPool& commandPool) {
    vkFreeCommandBuffers(device, commandPool, static_cast<std::uint32_t>(m_CommandBuffers.size()),
                         m_CommandBuffers.data());
}
