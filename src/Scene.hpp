#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <optional>
#include <vector>

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
    inline void createSurface();
    inline void createSwapChain();
    inline void createImageViews();
    inline void createRenderPass();
    inline void createGraphicsPipeline();
    inline void createFramebuffers();
    inline void createCommandPool();
    inline void createCommandBuffers(); 
    inline void createSyncObjects();
    inline void drawFrame();

    inline void recreateSwapChain();
    inline void cleanupSwapChain();

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    bool isDeviceSuitable(VkPhysicalDevice device);
    int rateDeviceSuitability(VkPhysicalDevice device);

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    VkShaderModule createShaderModule(const std::vector<char>& code);

    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

    GLFWwindow* window;
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    VkQueue graphicsQueue;

    VkSurfaceKHR surface;
    VkQueue presentQueue;
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;

    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;

    std::vector<VkFramebuffer> swapChainFramebuffers;
    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;

    const int MAX_FRAMES_IN_FLIGHT = 2;
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;
    size_t currentFrame;

    bool framebufferResized;


};