#include "CommandStructure.hpp"

void CommandStructure::createCommandPool(QueueFamilyIndices queueFamilyIndices, VkDevice device)
{
    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    // Selecting graphicsFamily in order to issue draw commands in this command pool
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

    if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create command pool!");
    }
}

void CommandStructure::createCommandBuffers(VkDevice device, const int maxFrames)
{
    commandBuffers.resize(maxFrames);

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = commandPool;
    /*
        VK_COMMAND_BUFFER_LEVEL_PRIMARY: Can be submitted to a queue for execution, but cannot be called from other command buffers.
        VK_COMMAND_BUFFER_LEVEL_SECONDARY: Cannot be submitted directly, but can be called from primary command buffers.
    */
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

    if (vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }
}

void CommandStructure::recordCommandBuffer(VkCommandBuffer cmdBuffer, uint32_t imageIndex, VkRenderPass renderPass,
                                           std::vector<VkFramebuffer>scFramebuffers, 
                                           VkExtent2D scExtent, 
                                           VkPipeline gPipeline,
                                           VkBuffer vBuffer, VkBuffer iBuffer, VkPipelineLayout pLayout, 
                                           std::vector<VkDescriptorSet> dSets, uint32_t cFrame, 
                                           std::vector<uint32_t> indices)
{
    /*
            If the command buffer was already recorded once, then a call to vkBeginCommandBuffer will implicitly reset it.
            It's not possible to append commands to a buffer at a later time.
        */
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    // BEGIN RECORDING 
    if (vkBeginCommandBuffer(cmdBuffer, &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("failed to begin recording command buffer!");
    }

    // BEGIN RENDER PASS
    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = renderPass;
    renderPassInfo.framebuffer = scFramebuffers[imageIndex];
    renderPassInfo.renderArea.offset = { 0, 0 };
    renderPassInfo.renderArea.extent = scExtent;
    // VK_ATTACHMENT_LOAD_OP_CLEAR clear values for color and depth stencil
    std::array<VkClearValue, 2> clearValues{};
    clearValues[0].color = { {0.0f, 0.0f, 0.0f, 1.0f} };
    clearValues[1].depthStencil = { 1.0f, 0 };
    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    renderPassInfo.pClearValues = clearValues.data();
    vkCmdBeginRenderPass(cmdBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
    // Binding the graphics pipeline
    vkCmdBindPipeline(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, gPipeline);

    // We set the viewport and scissor state as dynamic in the pipeline 
    // We need to set those up in the command buffer now  
    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(scExtent.width);
    viewport.height = static_cast<float>(scExtent.height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(cmdBuffer, 0, 1, &viewport);
    VkRect2D scissor{};
    scissor.offset = { 0, 0 };
    scissor.extent = scExtent;
    vkCmdSetScissor(cmdBuffer, 0, 1, &scissor);


    VkBuffer vertexBuffers[] = { vBuffer };
    VkDeviceSize offsets[] = { 0 };

    // BIND VERTEX & INDEX BUFFERS AS WELL AS DESCRIPTOR SETS
    vkCmdBindVertexBuffers(cmdBuffer, 0, 1, vertexBuffers, offsets);
    vkCmdBindIndexBuffer(cmdBuffer, iBuffer, 0, VK_INDEX_TYPE_UINT32);
    vkCmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pLayout, 0, 1,
        &dSets[cFrame], 0, nullptr);

    /*
        vkCmdDraw(VkCommandBuffer, vertexCount, instanceCount, firstVertex, firstInstance)
        vertexCount: Even though we don't have a vertex buffer, we technically still have 3 vertices to draw.
        instanceCount: Used for instanced rendering, use 1 if you're not doing that.
        firstVertex: Used as an offset into the vertex buffer, defines the lowest value of gl_VertexIndex.
        firstInstance: Used as an offset for instanced rendering, defines the lowest value of gl_InstanceIndex.
    */
    //vkCmdDraw(commandBuffer, static_cast<uint32_t>(vertices.size()), 1, 0, 0);
    vkCmdDrawIndexed(cmdBuffer, static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);

    vkCmdEndRenderPass(cmdBuffer);

    // END RECORDING
    if (vkEndCommandBuffer(cmdBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to record command buffer!");
    }

}

