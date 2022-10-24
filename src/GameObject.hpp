#pragma once
#include <memory>

#include "Model.hpp"
class GameObject {
public:
    static GameObject createGameObject();
    ~GameObject();

    GameObject(const Device &) = delete;
    GameObject operator=(const Device &) = delete;
    GameObject(GameObject &&) = default;
    GameObject &operator=(GameObject &&) = default;

    uint64_t getId() const {return uid;}

    std::shared_ptr<Model> model;
    glm::vec3 color;
    glm::vec3 position;
    glm::vec3 rotation;
    float size;

private:
    GameObject(uint64_t id);
    uint64_t uid;
    
};
