#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
// To meet Vulkan data alignment specs
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

// Textures through stb library
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <chrono>
#include <iostream>
#include <array>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <map>
#include <optional>
#include <set>
#include <cstdint> // Necessary for uint32_t
#include <limits> // Necessary for std::numeric_limits
#include <algorithm> // Necessary for std::clamp
#include <fstream>
#include <glm/glm.hpp>
#include <unordered_map>


struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class Initializer {
public:
#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif
    

private:

// CONSTANTS
    const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
    const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

// CLASS MEMBERS
    // m_ denotes private member
    VkInstance m_instance;
    VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
    VkDebugUtilsMessengerEXT m_debugMessenger;

    // r_ denotes private member returned in public
    VkSurfaceKHR r_surface;
    VkDevice r_device;
    VkQueue r_graphicsQueue;
    VkQueue r_presentQueue;

// CORE FUNCTIONS
    void createInstance();
    void setupDebugMessenger();
    void createSurface();
    void pickPhysicalDevice();
    void createLogicalDevice();


// HELPER FUNCTIONS
    // Used by createInstance()
    bool checkValidationLayerSupport();
    std::vector<const char*> getRequiredExtensions();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    // Used by pickPhysicalDevice()
    bool isDeviceSuitable(VkPhysicalDevice device);

    // Used by isDeviceSuitable()
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    // Used by isDeviceSuitable() and createLogicalDevice()
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    
    // Used by populateDebugMessengerCreateInfo()
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                        VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                        void* pUserData);
    // Used by setupDebugMessenger()
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
                                          const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                          const VkAllocationCallbacks* pAllocator,
                                          VkDebugUtilsMessengerEXT* pDebugMessenger);
};