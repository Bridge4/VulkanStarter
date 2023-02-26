#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdexcept>

class ImageView
{
public: 
    static VkImageView create(VkDevice device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
};

