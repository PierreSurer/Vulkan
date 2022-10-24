#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>


Camera::Camera() : fov(70.0f), near(0.01f), far(150.0f) {
}

Camera::~Camera() {
}

void Camera::update(float width, float height) {
    projection = glm::perspective(fov, std::max(width, height) / std::min(width, height), near, far);
}