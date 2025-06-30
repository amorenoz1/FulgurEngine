#include "VulkanContext.hpp"
#include "utils/FulgurUtils.hpp"
#include "utils/Logger.hpp"
#include <iostream>
#include <string>
#include <vector>

static VKAPI_ATTR VkBool32 VKAPI_CALL
debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
              VkDebugUtilsMessageTypeFlagsEXT messageType,
              const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {

    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
                                      const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                      const VkAllocationCallbacks* pAllocator,
                                      VkDebugUtilsMessengerEXT* pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
        instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                   const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
        instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}

bool Gfx::VulkanContext::CheckForValidationLayersSupport() {
    std::uint32_t validationLayersCount = 0;
    vkEnumerateInstanceLayerProperties(&validationLayersCount, nullptr);

    std::vector<VkLayerProperties> availableValidationLayers(validationLayersCount);
    vkEnumerateInstanceLayerProperties(&validationLayersCount, availableValidationLayers.data());

    for (const char* vl : m_ValidationLayers) {
        bool found = false;
        for (VkLayerProperties vlp : availableValidationLayers) {
            if (std::strcmp(vl, vlp.layerName) == 0) {
                found = true;
                break;
            }
        }

        if (!found) {
            return false;
        }
    }
    return true;
}

void Gfx::VulkanContext::CheckForExtensionsSupport(const char** extensions,
                                                   std::uint32_t& extension_count) {
    std::uint32_t availableExtensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(availableExtensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionCount,
                                           availableExtensions.data());

    for (std::uint32_t i = 0; i < extension_count; i++) {
        std::string extension = extensions[i];
        bool found = false;

        for (std::uint32_t j = 0; j < availableExtensionCount; j++) {
            std::string availableExtension = availableExtensions[j].extensionName;
            if (extension == availableExtension) {
                found = true;
                break;
            }
        }

        if (!found) {
            LOG_WARNING("Extension: " + extension + "not found!");
            break;
        }
    }
}

std::vector<const char*> Gfx::VulkanContext::GetRequiredExtensions() {
    std::uint32_t glfwExtensionCount = 0;

    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    CheckForExtensionsSupport(glfwExtensions, glfwExtensionCount);

    std::vector<const char*> requiredExtensions;

    for (std::uint32_t i = 0; i < glfwExtensionCount; i++) {
        requiredExtensions.emplace_back(glfwExtensions[i]);
    }

#ifdef __APPLE__
    requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#endif

    if (m_EnableValidationLayers) {
        requiredExtensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return requiredExtensions;
}

void Gfx::VulkanContext::CreateInstance() {
    VkApplicationInfo appInfo{
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pNext = nullptr,
        .pApplicationName = "Engine",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = "FulgurEngine",
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_3,
    };

    std::vector<const char*> requiredExtensions = GetRequiredExtensions();

    VkInstanceCreateInfo createInfo{
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pNext = nullptr,
        .pApplicationInfo = &appInfo,
        .enabledLayerCount = 0,
        .ppEnabledLayerNames = nullptr,
        .enabledExtensionCount = static_cast<std::uint32_t>(requiredExtensions.size()),
        .ppEnabledExtensionNames = requiredExtensions.data(),
    };

#ifdef __APPLE__
    createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#endif

    if (m_EnableValidationLayers) {
        Utils::Assert(CheckForValidationLayersSupport(),
                      "Validation Layers requested, but not supported!");
        createInfo.enabledLayerCount = static_cast<std::uint32_t>(m_ValidationLayers.size());
        createInfo.ppEnabledLayerNames = m_ValidationLayers.data();
    }

    VkResult instanceCreationRes = vkCreateInstance(&createInfo, nullptr, &m_Instance);

    Utils::Assert(instanceCreationRes == VK_SUCCESS, "Creation of VkInstance failed!");

    LOG_INFO("VkInstance creation was successful!");
}

void Gfx::VulkanContext::SetupDebugUtilsMessenger() {
    if (!m_EnableValidationLayers)
        return;

    VkDebugUtilsMessengerCreateInfoEXT createInfo{
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
        .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                       VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                       VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
        .pfnUserCallback = debugCallback,
        .pUserData = nullptr,
    };

    VkResult debugMessengerCreationRes =
        CreateDebugUtilsMessengerEXT(m_Instance, &createInfo, nullptr, &m_DebugUtilsMessenger);

    Utils::Assert(debugMessengerCreationRes == VK_SUCCESS, "Creation of DebugMessenger failed!");

    LOG_INFO("VkDebugMessenger creation was successful!");
}

VkInstance& Gfx::VulkanContext::GetVulkanInstance() { return m_Instance; }

void Gfx::VulkanContext::CreateContext() {
    CreateInstance();
    SetupDebugUtilsMessenger();
}

void Gfx::VulkanContext::CleanupContext() {
    if (m_EnableValidationLayers)
        DestroyDebugUtilsMessengerEXT(m_Instance, m_DebugUtilsMessenger, nullptr);
    vkDestroyInstance(m_Instance, nullptr);
}
