#include "GameObject.hpp"

GameObject GameObject::createGameObject() {
    static uint64_t currentId = 0;
    return GameObject(currentId++);

}

GameObject::GameObject(uint64_t id) : uid(id) {
}

GameObject::~GameObject() {
}
