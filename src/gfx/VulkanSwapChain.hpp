#pragma once
#include "VulkanDevice.hpp"
#include "core/FulgurCore.hpp"

namespace Gfx {
class VulkanSwapChain {
  private:
    VkSurfaceFormatKHR m_SurfaceFormat;
    VkPresentModeKHR m_SurfacePresentMode;
    VkExtent2D m_Extent;

    VkSwapchainKHR m_SwapChain;

    std::vector<VkImage> m_SwapChainImages;
    std::vector<VkImageView> m_SwapChainImageViews;

    void CreateImageViews(VkDevice& device);

    VkSurfaceFormatKHR
    ChooseSwapChainFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR
    ChooseSwapChainPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D ChooseSwapChainExtent(const VkSurfaceCapabilitiesKHR& availalbeCapabilities,
                                     GLFWwindow* window);

  public:
    void CreateSwapChain(VkDevice& device, VkSurfaceKHR& surface, QueueFamiliesIndices indices,
                         SwapChainSupportDetails details, GLFWwindow* window);
    VkSwapchainKHR& GetSwapChain();
    std::vector<VkImage>& GetImages();
    std::vector<VkImageView>& GetImageViews();
    VkExtent2D& GetExtent2D();
    VkSurfaceFormatKHR& GetSurfaceFormat();
    VkPresentModeKHR& GetPresentMode();
    void CleanupSwapChain(VkDevice& device);
};

}; // namespace Gfx
