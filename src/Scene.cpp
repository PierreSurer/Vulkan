#include "Scene.hpp"

#include "SimpleRenderSystem.hpp"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const std::vector<const char*> validationLayers = { //TODO more validation layers
    "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#ifdef NDEBUG
    constexpr bool enableValidationLayers = false;
#else
    constexpr bool enableValidationLayers = true;
#endif

Scene::Scene() : window(WIDTH, HEIGHT), device(window), renderer(this->window, this->device){
    loadGameObjects();
}

Scene::~Scene() {
}

void Scene::updateGameObjects() {
    for(auto& obj : gameObjects) {
        obj.rotation.y += .01f;
    }
}

void Scene::loadGameObjects() {
    std::vector<Model::Vertex> vertices {
        {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
        {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
    };

    auto model = std::make_shared<Model>(device, vertices);

    auto triangle = GameObject::createGameObject();
    triangle.model = model;
    triangle.position.z = -2.0f;

    gameObjects.push_back(std::move(triangle));
}

void Scene::run() {
    SimpleRenderSystem simpleRenderSystem(device, renderer.getSwapChainRenderPass());

    while (!window.shouldClose()) {
        glfwPollEvents();
        updateGameObjects();
        auto extent = window.getExtent();
        mainCamera.update((float)extent.width, (float)extent.height); //TODO optimize

        if (auto commandBuffer = renderer.beginFrame()) {
            renderer.beginSwapChainRenderPass(commandBuffer);
            simpleRenderSystem.renderGameObjects(commandBuffer, mainCamera, gameObjects);
            renderer.endSwapChainRenderPass(commandBuffer);
            renderer.endFrame();
        }
    }
    vkDeviceWaitIdle(device.getDevice());
}