#include "GameObject.hpp"

GameObject GameObject::createGameObject() {
    static uint64_t currentId = 0;
    return GameObject(currentId++);

}

GameObject::GameObject(uint64_t id) : uid(id), position(0.f), velocity(0.f), rotation(0.f), size(1.0f), mass(1.0f) {
}

GameObject::~GameObject() {
}

void GameObject::update(const float& dt) {
    //rotation.x += 20.0f * dt;
}