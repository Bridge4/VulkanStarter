/*
#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <iostream>
#include <array>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <map>
#include <optional>
#include <set>
#include <cstdint>        // Necessary for uint32_t
#include <limits>         // Necessary for std::numeric_limits
#include <algorithm>      // Necessary for std::clamp
#include <fstream>
#include <unordered_map>

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

VkInstance instance;
VkDebugUtilsMessengerEXT m_debugMessenger;

class Instance {
public:
#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif
    Instance(std::string appName, std::string engineName, uint32_t apiVer);

    VkInstance getInstance() { return instance; }

    void destroyInstance();

private:
    VkInstance instance;

    void createInstance(std::string appName, std::string engineName, uint32_t apiVer);

    std::vector<const char*> getRequiredExtensions();

    // DEBUG
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
        const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

    void setupDebugMessenger();

    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
        const VkAllocationCallbacks* pAllocator);
};



*/