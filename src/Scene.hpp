#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class Scene {
public:
    Scene();
    ~Scene();

    void run();

private:
    inline void createVkInstance();
    inline bool checkValidationLayerSupport(); // debug only
    inline void pickPhysicalDevice();
    inline void createLogicalDevice();

    GLFWwindow* window;
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    VkQueue graphicsQueue;

};