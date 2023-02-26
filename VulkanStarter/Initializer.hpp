#pragma once
#define VK_USE_PLATFORM_WIN32_KHR

#include <iostream>
#include <array>
#include <set>
#include <vector>
#include <optional>
#include <cstdint> // Necessary for uint32_t
#include "Window.hpp"

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

    //~Initializer();

    void init(Window* window);

    VkSurfaceKHR surface() { return r_surface; }

    VkPhysicalDevice physDevice() { return r_physicalDevice; }

    VkDevice logDevice() { return r_device; }

    VkQueue graphicsQueue() { return r_graphicsQueue; }

    VkQueue presentQueue() { return r_presentQueue; }

    void destroy();

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    // Used by isDeviceSuitable() and createLogicalDevice()
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

private:
    // CONSTANTS
    const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
    const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

    // CLASS ME
    VkInstance m_instance;
    VkDebugUtilsMessengerEXT m_debugMessenger;

    // r_ denotes private member accessed in public function
    VkSurfaceKHR r_surface;
    VkDevice r_device;
    VkPhysicalDevice r_physicalDevice = VK_NULL_HANDLE;
    VkQueue r_graphicsQueue;
    VkQueue r_presentQueue;

    // CORE FUNCTIONS
    
    void createInstance();
    void createDebugMessenger();
    void createSurface(Window window);
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

    // Used to destroy debugger
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

    // Used by destructor to...destroy everything
    
};