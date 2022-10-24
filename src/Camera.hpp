#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

class Camera
{
public:
    Camera();
    ~Camera();

    void update(float width, float height);
    glm::mat4 getProjection() const{ return projection; }
    
private:
    glm::mat4 projection;
    float fov;
    float near;
    float far;
    
};

