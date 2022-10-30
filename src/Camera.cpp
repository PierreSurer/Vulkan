#include "Camera.hpp"

#include <limits>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : fov(70.0f), near(0.01f), far(500.0f), 
    position(0.f), rotation(0.f),
    moveSpeed(3.0f), lookSpeed(120.0f) {
}

Camera::~Camera() {
}

void Camera::update(WindowManager* manager, float dt) {
    auto window = manager->getWindow();
    if (glfwGetKey(window, keys.lookRight) == GLFW_PRESS) rotation.y += lookSpeed * dt;
    if (glfwGetKey(window, keys.lookLeft) == GLFW_PRESS)  rotation.y -= lookSpeed * dt;
    if (glfwGetKey(window, keys.lookUp) == GLFW_PRESS)  rotation.x += lookSpeed * dt;
    if (glfwGetKey(window, keys.lookDown) == GLFW_PRESS)  rotation.x -= lookSpeed * dt;

    rotation.y = glm::mod(rotation.y, 360.0f);
    auto extent = manager->getExtent();
    if(extent.width != 0 && extent.height != 0)
        projection = glm::perspective(fov, (float)std::max(extent.width, extent.height) / (float)std::min(extent.width, extent.height), near, far);//TODO

    glm::mat4 transform{1.0f};
    transform = glm::rotate(transform, glm::radians(rotation.x), {1.0f, 0.0f, 0.0f});
    transform = glm::rotate(transform, glm::radians(rotation.y), {0.0f, 1.0f, 0.0f});

    projection *= transform;

    glm::vec3 moveDir{0.f};
    if (glfwGetKey(window, keys.moveForward) == GLFW_PRESS) moveDir -= glm::vec3(0.0f, 0.0f, 1.0f);
    if (glfwGetKey(window, keys.moveBackward) == GLFW_PRESS) moveDir += glm::vec3(0.0f, 0.0f, 1.0f);
    if (glfwGetKey(window, keys.moveRight) == GLFW_PRESS) moveDir += glm::vec3(1.0f, 0.0f, 0.0f);
    if (glfwGetKey(window, keys.moveLeft) == GLFW_PRESS) moveDir -= glm::vec3(1.0f, 0.0f, 0.0f);
    if (glfwGetKey(window, keys.moveUp) == GLFW_PRESS) moveDir += glm::vec3(0.0f, 1.0f, 0.0f);
    if (glfwGetKey(window, keys.moveDown) == GLFW_PRESS) moveDir -= glm::vec3(0.0f, 1.0f, 0.0f);

    moveDir = glm::vec4(moveDir, 1.0f) * transform;

    if (glm::dot(moveDir, moveDir) > std::numeric_limits<float>::epsilon()) {
        position += moveSpeed * dt * glm::normalize(moveDir);
    }

}