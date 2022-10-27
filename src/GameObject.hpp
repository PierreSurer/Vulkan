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
    
    void update(const float& dt);

    std::shared_ptr<Model> model;
    glm::vec3 color;
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 rotation;
    glm::vec3 size;
    float mass;

private:
    GameObject(uint64_t id);
    uint64_t uid;
    
};
