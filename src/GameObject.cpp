#include "GameObject.hpp"

GameObject GameObject::createGameObject() {
    static uint64_t currentId = 0;
    return GameObject(currentId++);

}

GameObject::GameObject(uint64_t id) : uid(id), color(1.0f), position(0.f), rotation(0.f), size(1.0f) {
}

GameObject::~GameObject() {
}
