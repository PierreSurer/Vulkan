#pragma once

#include <memory>
#include <vector>

#include "WindowManager.hpp"
#include "Device.hpp"
#include "Pipeline.hpp"
#include "SwapChain.hpp"

class Scene {
public:
    Scene();
    ~Scene();

    Scene(const Scene&) = delete;
    void operator=(const Scene&) = delete;

    void run();

private:
    void createPipelineLayout();
    void createPipeline();
    void createCommandBuffer();

    void drawFrame();

    WindowManager window;
    Device device;
    SwapChain swapChain;
    std::unique_ptr<Pipeline> pipeline;
    VkPipelineLayout pipelineLayout;
    std::vector<VkCommandBuffer> commandBuffers;

};