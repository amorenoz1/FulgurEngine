#pragma once

#include "core/FulgurCore.hpp"
#include <array>
#include <cstdint>
#include <vector>

namespace Gfx {

class VulkanContext {
  private:
    VkInstance m_Instance;
    VkDebugUtilsMessengerEXT m_DebugUtilsMessenger;

    const std::array<const char*, 1> m_ValidationLayers = {"VK_LAYER_KHRONOS_validation"};

#ifdef DEBUG
    const bool m_EnableValidationLayers = true;
#else
    const bool enableValidationLayers = false;
#endif

    std::vector<const char*> GetRequiredExtensions();
    void CreateInstance();
    void SetupDebugUtilsMessenger();
    void CheckForExtensionsSupport(const char** extensions, std::uint32_t& extension_count);
    bool CheckForValidationLayersSupport();

  public:
    VulkanContext() = default;
    ~VulkanContext() = default;

    VulkanContext(const VulkanContext&) = delete;
    VulkanContext& operator=(const VulkanContext&) = delete;

    void CreateContext();
    void CleanupContext();

    VkInstance& GetVulkanInstance();
    VkDebugUtilsMessengerEXT& GetDebugUtilsMesseneger();
};

} // namespace Gfx
