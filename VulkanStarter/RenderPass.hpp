#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <stdexcept>
#include <array>

class RenderPass
{
public:
	VkRenderPass renderPass;

	void create(VkFormat swapChainImageFormat, VkPhysicalDevice pDevice, VkDevice device);

    void destroy(VkDevice device) { vkDestroyRenderPass(device, renderPass, nullptr); }

    // TODO: Find a good place to put this generic function as its accessed by createDepthResources() too
    VkFormat findDepthFormat(VkPhysicalDevice pDevice);

private:

    

    // used by findDepthFormat()
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features, VkPhysicalDevice pDevice);
};

