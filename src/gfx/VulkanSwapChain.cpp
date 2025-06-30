#include "VulkanSwapChain.hpp"
#include "utils/FulgurUtils.hpp"
#include "utils/Logger.hpp"

#include <algorithm>

void Gfx::VulkanSwapChain::CreateSwapChain(VkDevice& device, VkSurfaceKHR& surface,
                                           Gfx::QueueFamiliesIndices indices,
                                           Gfx::SwapChainSupportDetails details,
                                           GLFWwindow* window) {
    m_SurfaceFormat = ChooseSwapChainFormat(details.m_Formats);
    m_SurfacePresentMode = ChooseSwapChainPresentMode(details.m_PresentMode);
    m_Extent = ChooseSwapChainExtent(details.m_Capabilities, window);

    std::uint32_t imageCount = details.m_Capabilities.minImageCount + 1;

    if (details.m_Capabilities.maxImageCount > 0 &&
        imageCount > details.m_Capabilities.maxImageCount) {
        imageCount = details.m_Capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo{
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext = nullptr,
        .flags = 0,
        .surface = surface,
        .minImageCount = imageCount,
        .imageFormat = m_SurfaceFormat.format,
        .imageColorSpace = m_SurfaceFormat.colorSpace,
        .imageExtent = m_Extent,
        .imageArrayLayers = 1,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .preTransform = details.m_Capabilities.currentTransform,
        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .presentMode = m_SurfacePresentMode,
        .clipped = VK_TRUE,
        .oldSwapchain = VK_NULL_HANDLE,
    };

    std::uint32_t queueFamilyIndices[] = {indices.m_GraphicsFamily.value(),
                                          indices.m_PresentFamily.value()};

    if (indices.m_GraphicsFamily != indices.m_PresentFamily) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    } else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0;
        createInfo.pQueueFamilyIndices = nullptr;
    }

    VkResult SwapChainCreationRes =
        vkCreateSwapchainKHR(device, &createInfo, nullptr, &m_SwapChain);
    Utils::Assert(SwapChainCreationRes == VK_SUCCESS, "Creation of Swapchain failed!");
    LOG_INFO("VkSwapchain creation was successful!");

    vkGetSwapchainImagesKHR(device, m_SwapChain, &imageCount, nullptr);
    m_SwapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(device, m_SwapChain, &imageCount, m_SwapChainImages.data());

    CreateImageViews(device);
}

VkExtent2D& Gfx::VulkanSwapChain::GetExtent2D() { return m_Extent; }

VkSurfaceFormatKHR& Gfx::VulkanSwapChain::GetSurfaceFormat() { return m_SurfaceFormat; }

VkPresentModeKHR& Gfx::VulkanSwapChain::GetPresentMode() { return m_SurfacePresentMode; }

VkSwapchainKHR& Gfx::VulkanSwapChain::GetSwapChain() { return m_SwapChain; }

std::vector<VkImage>& Gfx::VulkanSwapChain::GetImages() { return m_SwapChainImages; }

std::vector<VkImageView>& Gfx::VulkanSwapChain::GetImageViews() { return m_SwapChainImageViews; }

void Gfx::VulkanSwapChain::CreateImageViews(VkDevice& device) {
    m_SwapChainImageViews.resize(m_SwapChainImages.size());

    for (std::size_t i = 0; i < m_SwapChainImages.size(); i++) {
        VkImageViewCreateInfo createInfo{
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .image = m_SwapChainImages[i],
            .viewType = VK_IMAGE_VIEW_TYPE_2D,
            .format = m_SurfaceFormat.format,
            .components.r = VK_COMPONENT_SWIZZLE_IDENTITY,
            .components.g = VK_COMPONENT_SWIZZLE_IDENTITY,
            .components.b = VK_COMPONENT_SWIZZLE_IDENTITY,
            .components.a = VK_COMPONENT_SWIZZLE_IDENTITY,
            .subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
            .subresourceRange.baseMipLevel = 0,
            .subresourceRange.levelCount = 1,
            .subresourceRange.baseArrayLayer = 0,
            .subresourceRange.layerCount = 1,
        };
        VkResult imageViewCreationRes =
            vkCreateImageView(device, &createInfo, nullptr, &m_SwapChainImageViews[i]);
        Utils::Assert(imageViewCreationRes == VK_SUCCESS, "VkImageView creation failed!");
    }
}

VkSurfaceFormatKHR Gfx::VulkanSwapChain::ChooseSwapChainFormat(
    const std::vector<VkSurfaceFormatKHR>& availableFormats) {
    for (const auto& availableFormat : availableFormats) {
        if (availableFormat.format == VK_FORMAT_R8G8B8A8_SRGB &&
            availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return availableFormat;
        }
    }

    if (!availableFormats.empty()) {
        return availableFormats[0];
    }

    LOG_ERROR("No available surface formats!");
    return {VK_FORMAT_UNDEFINED, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
}

VkPresentModeKHR Gfx::VulkanSwapChain::ChooseSwapChainPresentMode(
    const std::vector<VkPresentModeKHR>& availablePresentModes) {
    for (const auto& availablePresentMode : availablePresentModes) {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
            return availablePresentMode;
        }
        if (availablePresentMode == VK_PRESENT_MODE_FIFO_RELAXED_KHR) {
            return availablePresentMode;
        }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D
Gfx::VulkanSwapChain::ChooseSwapChainExtent(const VkSurfaceCapabilitiesKHR& availableCapabilities,
                                            GLFWwindow* window) {
    if (availableCapabilities.currentExtent.width != std::numeric_limits<std::uint32_t>::max()) {
        return availableCapabilities.currentExtent;
    }
    std::int32_t width, height;
    glfwGetFramebufferSize(window, &width, &height);

    VkExtent2D extent{.width = static_cast<std::uint32_t>(width),
                      .height = static_cast<std::uint32_t>(height)};

    extent.width = std::clamp(extent.width, availableCapabilities.minImageExtent.width,
                              availableCapabilities.maxImageExtent.width);
    extent.height = std::clamp(extent.height, availableCapabilities.minImageExtent.height,
                               availableCapabilities.maxImageExtent.height);

    return extent;
}

void Gfx::VulkanSwapChain::CleanupSwapChain(VkDevice& device) {
    for (auto& imageView : m_SwapChainImageViews) {
        vkDestroyImageView(device, imageView, nullptr);
    }

    vkDestroySwapchainKHR(device, m_SwapChain, nullptr);
}
