#include "VulkanCommandPool.hpp"
#include "utils/FulgurUtils.hpp"
#include "utils/Logger.hpp"
#include <vulkan/vulkan_core.h>

void Gfx::VulkanCommandPool::CreateCommandPool(VkDevice& device, QueueFamiliesIndices indices) {
    VkCommandPoolCreateInfo createInfo{.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
                                       .pNext = nullptr,
                                       .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
                                       .queueFamilyIndex = indices.m_GraphicsFamily.value()};

    VkResult commandPoolCreationRes =
        vkCreateCommandPool(device, &createInfo, nullptr, &m_CommandPool);

    Utils::Assert(commandPoolCreationRes == VK_SUCCESS, "VkCommandPool creation failed!");

    LOG_INFO("VkCommandPool creation was successful!");
}

VkCommandPool& Gfx::VulkanCommandPool::GetCommandPool() { return m_CommandPool; }
void Gfx::VulkanCommandPool::CleanupCommandPool(VkDevice& device) {
    vkDestroyCommandPool(device, m_CommandPool, nullptr);
}
