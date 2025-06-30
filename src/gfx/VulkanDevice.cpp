#include "VulkanDevice.hpp"
#include "utils/FulgurUtils.hpp"
#include "utils/Logger.hpp"

#include <algorithm>
#include <cstdint>
#include <set>
#include <sstream>
#include <utility>
#include <vector>
#include <vulkan/vulkan_core.h>

// ============================================================================
// Public Interface
// ============================================================================

void Gfx::VulkanDevice::CreateDevice(VkInstance& instance, GLFWwindow* window) {
    CreateSurface(instance, window);
    ChoosePhysicalDevice(instance);
    CreateLogicalDevice(instance);
}

void Gfx::VulkanDevice::CreateSurface(VkInstance& instance, GLFWwindow* window) {
    VkResult result = glfwCreateWindowSurface(instance, window, nullptr, &m_Surface);

    Utils::Assert(result == VK_SUCCESS, "Failed to create Vulkan window surface!");

    LOG_INFO("VkSurface creation was successful!");
}

VkSurfaceKHR& Gfx::VulkanDevice::GetSurface() { return m_Surface; }

VkDevice& Gfx::VulkanDevice::GetLogicalDevice() { return m_Device; }

VkPhysicalDevice& Gfx::VulkanDevice::GetPhysicalDevice() { return m_PhysicalDevice; }

void Gfx::VulkanDevice::CleanupDevice(VkInstance& instance) {
    vkDestroySurfaceKHR(instance, m_Surface, nullptr);
    vkDestroyDevice(m_Device, nullptr);
}

Gfx::QueueFamiliesIndices Gfx::VulkanDevice::FindQueueFamilies() {
    return FindQueueFamilies(m_PhysicalDevice, m_Surface);
}

Gfx::SwapChainSupportDetails Gfx::VulkanDevice::QuerySwapChainSupport() {
    return QuerySwapChainSupport(m_PhysicalDevice, m_Surface);
}

// ============================================================================
// Device Extension Support
// ============================================================================

bool Gfx::VulkanDevice::CheckDeviceExtensionSupport(VkPhysicalDevice device) {
    // Get available extensions count
    uint32_t extensionCount = 0;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    // Get available extensions
    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount,
                                         availableExtensions.data());

// Create set of required extensions for efficient lookup
#ifdef __APPLE__
    m_DeviceExtensions.push_back("VK_KHR_portability_subset");
#endif

    std::set<std::string> requiredExtensions(m_DeviceExtensions.begin(), m_DeviceExtensions.end());

    // Remove found extensions from required set
    for (const auto& extension : availableExtensions) {
        requiredExtensions.erase(extension.extensionName);
    }

    // All extensions supported if set is empty
    return requiredExtensions.empty();
}

// ============================================================================
// Device Suitability and Rating
// ============================================================================

bool Gfx::VulkanDevice::IsDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface) {
    QueueFamiliesIndices indices = FindQueueFamilies(device, surface);
    bool extensionsSupported = CheckDeviceExtensionSupport(device);

    bool SwapChainSupported = false;
    if (extensionsSupported) {
        SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(device, surface);
        SwapChainSupported =
            !swapChainSupport.m_PresentMode.empty() && !swapChainSupport.m_Formats.empty();
    }

    return indices.m_GraphicsFamily.has_value() && indices.m_PresentFamily.has_value() &&
           extensionsSupported && SwapChainSupported;
}

Gfx::SwapChainSupportDetails Gfx::VulkanDevice::QuerySwapChainSupport(VkPhysicalDevice& device,
                                                                      VkSurfaceKHR& surface) {
    SwapChainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.m_Capabilities);

    std::uint32_t formatCount = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

    Utils::Assert(formatCount != 0, "No formats available!");

    details.m_Formats.resize(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.m_Formats.data());

    std::uint32_t presentCount = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentCount, nullptr);

    Utils::Assert(presentCount != 0, "No present modes available");

    details.m_PresentMode.resize(formatCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentCount,
                                              details.m_PresentMode.data());

    return details;
}

std::int32_t Gfx::VulkanDevice::RatePhysicalDevice(VkPhysicalDevice device) {
    VkPhysicalDeviceProperties properties;
    VkPhysicalDeviceFeatures features;
    vkGetPhysicalDeviceProperties(device, &properties);
    vkGetPhysicalDeviceFeatures(device, &features);

    LOG_TRACE("Checking GPU = " + std::string(properties.deviceName));

    std::int32_t score = 0;

    // Device type scoring
    if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
        score += 1000; // Prefer discrete GPUs
    } else if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU) {
        score -= 100; // Penalize integrated GPUs slightly
    } else if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_CPU) {
        score -= 1000; // Heavily penalize CPU rendering
    }

    // Hardware capability scoring
    score += static_cast<int32_t>(properties.limits.maxDescriptorSetSampledImages / 4);
    score += static_cast<int32_t>(properties.limits.maxPerStageDescriptorSampledImages / 4);
    score += static_cast<int32_t>(properties.limits.maxPerStageDescriptorSamplers / 4);
    score += static_cast<int32_t>(properties.limits.maxImageDimension2D);

    // Feature bonuses
    if (features.samplerAnisotropy) {
        score += 100;
    }

    if (features.geometryShader) {
        score += 100;
    }

    std::ostringstream ss;
    ss << score;

    LOG_TRACE("GPU Score = " + ss.str());

    // Required features check - return 0 if missing critical features
    if (!features.samplerAnisotropy || !features.geometryShader) {
        return 0;
    }

    return score;
}

// ============================================================================
// Queue Family Management
// ============================================================================

Gfx::QueueFamiliesIndices Gfx::VulkanDevice::FindQueueFamilies(VkPhysicalDevice device,
                                                               VkSurfaceKHR surface) {
    QueueFamiliesIndices indices;

    // Get queue family count
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    // Get queue families
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    // Search for suitable queue families
    std::uint32_t familyIndex = 0;
    for (const auto& queueFamily : queueFamilies) {

        // Check for graphics queue support
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.m_GraphicsFamily = familyIndex;
        }

        // Check for presentation support
        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, familyIndex, surface, &presentSupport);
        if (presentSupport) {
            indices.m_PresentFamily = familyIndex;
        }

        if (queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT) {
            indices.m_TransferFamily = familyIndex;
        }

        // Early exit if we found both required families
        if (indices.m_GraphicsFamily.has_value() && indices.m_PresentFamily.has_value() &&
            indices.m_PresentFamily.has_value()) {
            break;
        }

        ++familyIndex;
    }

    return indices;
}

// ============================================================================
// Physical Device Selection
// ============================================================================

void Gfx::VulkanDevice::ChoosePhysicalDevice(VkInstance& instance) {
    // Get physical device count
    std::uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    Utils::Assert(deviceCount != 0, "No Vulkan-compatible physical devices found.");

    // Get physical devices
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    // Evaluate and score suitable devices
    std::vector<std::pair<std::int32_t, VkPhysicalDevice>> candidates;

    for (VkPhysicalDevice& device : devices) {
        if (!IsDeviceSuitable(device, m_Surface)) {
            continue;
        }

        std::int32_t score = RatePhysicalDevice(device);
        candidates.emplace_back(score, device);
    }

    Utils::Assert(!candidates.empty(), "Failed to find a suitable physical device!");

    // Sort candidates by score (highest first)
    auto scoreComparator = [](const auto& deviceA, const auto& deviceB) {
        return deviceA.first < deviceB.first;
    };
    std::make_heap(candidates.begin(), candidates.end(), scoreComparator);

    // Select the best device
    m_PhysicalDevice = candidates.back().second;
    m_Indices = FindQueueFamilies(m_PhysicalDevice, m_Surface);
    m_Details = QuerySwapChainSupport(m_PhysicalDevice, m_Surface);

    LOG_INFO("VkPhysicalDevice selection was successful!");

    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(m_PhysicalDevice, &properties);

    LOG_INFO("GPU = " + std::string(properties.deviceName));
}

// ============================================================================
// Logical Device Creation
// ============================================================================

void Gfx::VulkanDevice::CreateLogicalDevice(VkInstance& instance) {
    // Get unique queue families (graphics and present might be the same)
    std::set<std::uint32_t> uniqueQueueFamilies = {m_Indices.m_GraphicsFamily.value(),
                                                   m_Indices.m_PresentFamily.value()};

    // Create queue create infos for each unique family
    std::float_t queuePriority = 1.0f;
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

    for (std::uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo{
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .queueFamilyIndex = queueFamily,
            .queueCount = 1,
            .pQueuePriorities = &queuePriority,
        };
        queueCreateInfos.push_back(queueCreateInfo);
    }

    // Specify device features (currently empty - add as needed)
    VkPhysicalDeviceFeatures deviceFeatures{};

    // Create the logical device
    VkDeviceCreateInfo createInfo{
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size()),
        .pQueueCreateInfos = queueCreateInfos.data(),
        .enabledExtensionCount = static_cast<uint32_t>(m_DeviceExtensions.size()),
        .ppEnabledExtensionNames = m_DeviceExtensions.data(),
        .pEnabledFeatures = &deviceFeatures,
    };

    VkResult result = vkCreateDevice(m_PhysicalDevice, &createInfo, nullptr, &m_Device);

    Utils::Assert(result == VK_SUCCESS, "Failed to create logical device.");

    LOG_INFO("VkLogicalDevice creation was successful!");
}
