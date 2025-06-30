#pragma once

#include "core/FulgurCore.hpp"
#include <cstdint>
#include <optional>
#include <vector>

namespace Gfx {
struct QueueFamiliesIndices {
    std::optional<std::uint32_t> m_GraphicsFamily;
    std::optional<std::uint32_t> m_PresentFamily;
    std::optional<std::uint32_t> m_TransferFamily;
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR m_Capabilities;
    std::vector<VkSurfaceFormatKHR> m_Formats;
    std::vector<VkPresentModeKHR> m_PresentMode;
};

class VulkanDevice {
  private:
    VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
    VkDevice m_Device;
    VkSurfaceKHR m_Surface;

    std::vector<const char*> m_DeviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    SwapChainSupportDetails m_Details;
    QueueFamiliesIndices m_Indices;

    void CreateSurface(VkInstance& instance, GLFWwindow* window);
    void ChoosePhysicalDevice(VkInstance& instance);
    void CreateLogicalDevice(VkInstance& instance);
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
    bool IsDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);

    QueueFamiliesIndices FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
    SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice& device, VkSurfaceKHR& surface);
    std::int32_t RatePhysicalDevice(VkPhysicalDevice device);

  public:
    VulkanDevice() = default;
    ~VulkanDevice() = default;

    VulkanDevice(const VulkanDevice&) = delete;
    VulkanDevice& operator=(const VulkanDevice&) = delete;

    void CreateDevice(VkInstance& instance, GLFWwindow* window);
    QueueFamiliesIndices FindQueueFamilies();
    SwapChainSupportDetails QuerySwapChainSupport();
    VkPhysicalDevice& GetPhysicalDevice();
    VkSurfaceKHR& GetSurface();
    VkDevice& GetLogicalDevice();
    void CleanupDevice(VkInstance& instance);
};
} // namespace Gfx
