#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class WindowManager {
public:
    WindowManager(int width, int height);
    ~WindowManager();

    //Can only have one reference to window
    WindowManager(const WindowManager&) = delete;
    WindowManager &operator=(const WindowManager&) = delete;

    bool shouldClose() {return glfwWindowShouldClose(window);};
    VkExtent2D getExtent() {return {(uint32_t)width, (uint32_t)height};}

    void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
private:
    int width;
    int height;
    GLFWwindow* window;
    
};
