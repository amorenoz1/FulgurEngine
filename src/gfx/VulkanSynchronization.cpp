#include "VulkanSynchronization.hpp"
#include "utils/FulgurUtils.hpp"
#include "utils/Logger.hpp"
#include <vulkan/vulkan_core.h>

void Gfx::VulkanSynchronizationElements::CreateSynchronizationElements(VkDevice& device) {
    m_ImageAvailableSems.resize(MAX_FRAMES_IN_FLIGHT);
    m_RenderFinishedSems.resize(MAX_FRAMES_IN_FLIGHT);
    m_InFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

    VkSemaphoreCreateInfo semCreateInfo{
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
    };

    VkFenceCreateInfo fenceCreateInfo{.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
                                      .pNext = nullptr,
                                      .flags = VK_FENCE_CREATE_SIGNALED_BIT};

    for (std::size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        VkResult imageAvailableSemCreationRes =
            vkCreateSemaphore(device, &semCreateInfo, nullptr, &m_ImageAvailableSems[i]);

        Utils::Assert(imageAvailableSemCreationRes == VK_SUCCESS, "VkSemaphore creation failed!");

        LOG_INFO("VkSemaphore creation was successful!");

        VkResult renderFinishedSemCreationRes =
            vkCreateSemaphore(device, &semCreateInfo, nullptr, &m_RenderFinishedSems[i]);

        Utils::Assert(renderFinishedSemCreationRes == VK_SUCCESS, "VkSemaphore creation failed!");

        LOG_INFO("VkSemaphore creation was successful!");

        VkResult inFlightFenceCreationRes =
            vkCreateFence(device, &fenceCreateInfo, nullptr, &m_InFlightFences[i]);

        Utils::Assert(inFlightFenceCreationRes == VK_SUCCESS, "VkSemaphore creation failed!");

        LOG_INFO("VkFence creation was successful!");
    }
}

std::vector<VkSemaphore>& Gfx::VulkanSynchronizationElements::GetImageAvailableSem() {
    return m_ImageAvailableSems;
}

std::vector<VkSemaphore>& Gfx::VulkanSynchronizationElements::GetRenderFinishedSem() {
    return m_RenderFinishedSems;
}

std::vector<VkFence>& Gfx::VulkanSynchronizationElements::GetInFlightFence() {
    return m_InFlightFences;
}

void Gfx::VulkanSynchronizationElements::CleanupSynchornizationElements(VkDevice& device) {
    for (std::size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(device, m_ImageAvailableSems[i], nullptr);
        vkDestroySemaphore(device, m_RenderFinishedSems[i], nullptr);
        vkDestroyFence(device, m_InFlightFences[i], nullptr);
    }
}
