#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "ImageView.hpp"
// This is a heavy include I'd like to clean up later. 
#include "Core.hpp"

// Including Initializer for the SwapChainSupportDetails struct
class SwapChain
{
public: 
    void create(Core init, Window window);

    void createImageViews(VkDevice device, ImageView imgV);

    void createFramebuffers(VkImageView depthImageView, VkRenderPass renderPass, VkDevice device); 

    void assign(VkSwapchainKHR* swapChain, VkFormat* scFormat, VkExtent2D* scExtent, std::vector<VkImageView>* scImageViews);

    VkSwapchainKHR get() { return m_swapChain; }

    VkFormat getImageFormat() { return m_swapChainImageFormat; }
    
    VkExtent2D getExtent() { return m_swapChainExtent; }

    std::vector<VkFramebuffer> getFramebuffers() { return m_swapChainFramebuffers; }

    std::vector<VkImageView> getImageViews() { return m_swapChainImageViews; }

private:
    VkSwapchainKHR m_swapChain;
    std::vector<VkImage> m_swapChainImages;
    std::vector<VkFramebuffer> m_swapChainFramebuffers;
    VkFormat m_swapChainImageFormat;
    VkExtent2D m_swapChainExtent;
    std::vector<VkImageView> m_swapChainImageViews;

    // HELPERS
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

    VkExtent2D chooseSwapExtent(Window window, const VkSurfaceCapabilitiesKHR& capabilities);
};

