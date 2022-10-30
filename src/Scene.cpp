#include "Scene.hpp"

#include <chrono>

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

void Scene::updateGameObjects(const float& dt) {
    for(auto& obj : gameObjects) {
        obj.update(dt);
    }
}

void Scene::loadGameObjects() {
    Model::Builder builder = createPlane(100.0f, 10, 6.0f);

    auto model = std::make_shared<Model>(device, builder);

    auto triangle = GameObject::createGameObject();
    triangle.model = model;
    triangle.position.y = 1.0f;

    gameObjects.push_back(std::move(triangle));
}

Model::Builder Scene::createPlane(float size, unsigned int subDivisions, float concentration) {
    int subSize = (int)pow(2.0, (double)subDivisions);
    std::vector<Model::Vertex> vertices((subSize + 1) * (subSize + 1));
    for(int i = 0; i <= subSize; i += 1) {
        for(int j = 0; j <= subSize; j += 1) {
            float x = (subSize - i - subSize / 2) / (float)subSize;
            float y = (subSize - j - subSize / 2) / (float)subSize;
            float dist = sqrt(x * x + y * y) * subSize;
            dist = std::max(dist, 1.0f);
            // https://arxiv.org/ftp/arxiv/papers/1509/1509.06344.pdf
            glm::vec3 pos;
            if(abs(x) >= abs(y))
                pos = {size * x * abs(x) / dist, 0.0f, size * y * abs(x) / dist};
            else
                pos = {size * x * abs(y) / dist, 0.0f, size * y * abs(y) / dist};

            pos *= subSize;

            float factor = pow(glm::length(pos) * 2.0f / size, concentration);
            

            pos *= factor;

            vertices.at(i * (subSize + 1) + j) = {
                pos,
                {x + 0.5f, y + 0.5f, 255.0f / 255.0f}
            };

            
        }
    }

    std::vector<uint32_t> indices(subSize * subSize * 2 * 3);
    for(int i = 0; i < subSize; i += 1) {
        for(int j = 0; j < subSize; j += 1) {
            indices.at((i * subSize + j) * 6 + 0) = (i + 0) * (subSize + 1) + j + 0;
            indices.at((i * subSize + j) * 6 + 1) = (i + 0) * (subSize + 1) + j + 1;
            indices.at((i * subSize + j) * 6 + 2) = (i + 1) * (subSize + 1) + j + 0;
            indices.at((i * subSize + j) * 6 + 3) = (i + 0) * (subSize + 1) + j + 1;
            indices.at((i * subSize + j) * 6 + 4) = (i + 1) * (subSize + 1) + j + 0;
            indices.at((i * subSize + j) * 6 + 5) = (i + 1) * (subSize + 1) + j + 1;
        }
    }
    return {vertices, indices};

}

void Scene::run() {
    SimpleRenderSystem simpleRenderSystem(device, renderer.getSwapChainRenderPass());

    auto currentTime = std::chrono::high_resolution_clock::now();
    double worldTime = 0.0;
    while (!window.shouldClose()) {
        glfwPollEvents();

        auto newTime = std::chrono::high_resolution_clock::now();
        float dt = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
        currentTime = newTime;
        worldTime += (double)dt;

        updateGameObjects(dt);
        mainCamera.update(&window, dt);

        if (auto commandBuffer = renderer.beginFrame()) {
            renderer.beginSwapChainRenderPass(commandBuffer);
            simpleRenderSystem.renderGameObjects(commandBuffer, mainCamera, gameObjects, worldTime);
            renderer.endSwapChainRenderPass(commandBuffer);
            renderer.endFrame();
        }
    }
    vkDeviceWaitIdle(device.getDevice());
}