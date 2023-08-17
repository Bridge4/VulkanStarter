#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdexcept>
#include "Buffer.hpp"
// Textures through stb library
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// This is a heavy include I'd like to clean up later. 

class Textures
{
	// Figuring out what how I want textures to work in the engine
public:
	void createBuffer() {  Buffer::create(VkDevice device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
		VkBuffer & buffer, VkDeviceMemory & bufferMemory) }
private:
	VkBuffer buffer;
};

