#pragma once

#include <memory>
#include <vector>

#include "WindowManager.hpp"
#include "Device.hpp"
#include "Pipeline.hpp"
#include "SwapChain.hpp"
#include "Model.hpp"

class Scene {
public:
    Scene();
    ~Scene();

    Scene(const Scene&) = delete;
    Scene operator=(const Scene&) = delete;

    void run();

private:
    void loadModels();
    void createPipelineLayout();
    void createPipeline();
    void createCommandBuffers();

    void drawFrame();

    void freeCommandBuffers();
    void recreateSwapChain();
    void recordCommandBuffer(int imageIndex);

    WindowManager window;
    Device device;
    std::unique_ptr<SwapChain> swapChain;
    std::unique_ptr<Pipeline> pipeline;
    VkPipelineLayout pipelineLayout;
    std::vector<VkCommandBuffer> commandBuffers;
    std::unique_ptr<Model> model;

};