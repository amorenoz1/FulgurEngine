#include "VulkanQueue.hpp"

void Gfx::VulkanQueue::RetrieveQueues(VkDevice& device, QueueFamiliesIndices indices) {
    vkGetDeviceQueue(device, indices.m_GraphicsFamily.value(), 0, &m_GraphicsQueue);
    vkGetDeviceQueue(device, indices.m_PresentFamily.value(), 0, &m_PresentQueue);
}

VkQueue& Gfx::VulkanQueue::GetPresentQueue() { return m_PresentQueue; }

VkQueue& Gfx::VulkanQueue::GetGraphicsQueue() { return m_GraphicsQueue; }

void Gfx::VulkanQueue::Cleanup() {}
