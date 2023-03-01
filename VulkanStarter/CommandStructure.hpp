#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "StructLib.hpp"
#include <stdexcept>


class CommandStructure
{
public:
	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
	
	void createCommandPool(QueueFamilyIndices queueFamilyIndices, VkDevice device);
	
	// Create command buffers for each frame in flight, default = 2
	void createCommandBuffers(VkDevice device, const int maxFrames=2);

	// Record commands into command buffer
	void recordCommandBuffer(VkCommandBuffer cmdBuffer, uint32_t imageIndex, VkRenderPass renderPass,
		std::vector<VkFramebuffer>scFramebuffers,
		VkExtent2D scExtent,
		VkPipeline gPipeline,
		VkBuffer vBuffer, VkBuffer iBuffer, VkPipelineLayout pLayout,
		std::vector<VkDescriptorSet> dSets, uint32_t cFrame,
		std::vector<uint32_t> indices = {});

private:

};

