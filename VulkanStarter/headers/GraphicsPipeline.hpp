#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "StructLib.hpp"

class GraphicsPipeline
{
public:
	VkPipeline graphicsPipeline;
    VkPipelineLayout pipelineLayout;

	void create(VkDevice device,
                VkExtent2D swapChainExtent,
                VkDescriptorSetLayout descriptorSetLayout,
                VkRenderPass renderPass);

    void destroy(VkDevice device);

private:
	
    // Reading in SPIRV shaders
	static std::vector<char> readFile(const std::string& filename);
    VkShaderModule createShaderModule(VkDevice device, const std::vector<char>& code); 
};

