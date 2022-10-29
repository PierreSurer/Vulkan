#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include "WindowManager.hpp"

class Camera
{
public:
    Camera();
    ~Camera();

    void update(WindowManager* window, float dt);
    glm::mat4 getProjection() const{ return projection; }

    glm::vec3 rotation;
    glm::vec3 position;

    struct KeyMappings {
        int moveLeft = GLFW_KEY_A;
        int moveRight = GLFW_KEY_D;
        int moveForward = GLFW_KEY_W;
        int moveBackward = GLFW_KEY_S;
        int moveUp = GLFW_KEY_E;
        int moveDown = GLFW_KEY_Q;
        int lookLeft = GLFW_KEY_LEFT;
        int lookRight = GLFW_KEY_RIGHT;
        int lookUp = GLFW_KEY_UP;
        int lookDown = GLFW_KEY_DOWN;
    };
    
private:
    KeyMappings keys;
    float moveSpeed;
    float lookSpeed;

    glm::mat4 projection;
    float fov;
    float near;
    float far;
    
};

