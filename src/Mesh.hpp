#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <array>

#include <vulkan/vulkan.h>

class Mesh {
public:
    Mesh();
    ~Mesh();

    static VkVertexInputBindingDescription getBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();

private:
    struct Vertex {
        glm::vec2 pos;
        glm::vec3 color;
    };
    
public:
    std::vector<Vertex> vertices;


};

