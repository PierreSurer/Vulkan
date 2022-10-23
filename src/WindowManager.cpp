#include "WindowManager.hpp"

#include <stdexcept>
#include "vulkan/vulkan.hpp"


WindowManager::WindowManager(int width, int height) : width(width), height(height) {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); //no resize

    window = glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);

}

WindowManager::~WindowManager() {
    glfwDestroyWindow(window);

    glfwTerminate();

}


void WindowManager::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface) {
    if(glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create window surface");
    }
}