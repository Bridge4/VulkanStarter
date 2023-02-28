#include "StructLib.hpp"


VkVertexInputBindingDescription Vertex::getBindingDescription() {
    VkVertexInputBindingDescription bindingDescription{};
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(Vertex);
    /*
        VK_VERTEX_INPUT_RATE_VERTEX: Move to the next data entry after each vertex
        VK_VERTEX_INPUT_RATE_INSTANCE: Move to the next data entry after each instance
    */
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    return bindingDescription;
}

std::array<VkVertexInputAttributeDescription, 3> Vertex::getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

        // position description
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].binding = 0;
        /*
            float: VK_FORMAT_R32_SFLOAT
            vec2:  VK_FORMAT_R32G32_SFLOAT
            vec3:  VK_FORMAT_R32G32B32_SFLOAT
            vec4:  VK_FORMAT_R32G32B32A32_SFLOAT
        */
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);
        // color description
        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        /*
            Color type (SFLOAT, UINT, SINT) and bit width should match to type of shader input
            ivec2: VK_FORMAT_R32G32_SINT, a 2-component vector of 32-bit signed integers
            uvec4: VK_FORMAT_R32G32B32A32_UINT, a 4-component vector of 32-bit unsigned integers
            double: VK_FORMAT_R64_SFLOAT, a double-precision (64-bit) float
        */
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

        return attributeDescriptions;
    }

bool Vertex::operator==(const Vertex & other) const {
    return pos == other.pos && color == other.color && texCoord == other.texCoord;
}




