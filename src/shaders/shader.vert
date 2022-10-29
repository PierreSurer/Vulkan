#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;

layout(location = 0) out vec3 fragColor;

layout(push_constant) uniform constants {
    mat4 transform;
    vec2 offset;
    double time;
} c;

float fourier(int k, vec2 loc, double time) {
    for(int i = 0; i < k; i++) {
        
    }

    return 0.0f;
}

void main() {
    vec3 pos = inPosition + vec3(c.offset.x, 0.0f, c.offset.y);
    pos.y -= 0.2f * (0.9f * sin(float(pos.x + 1.6f * c.time) - 0.4f) + 0.8f * cos(float(pos.z + 0.4f * c.time)));
    pos.y -= 0.5f * (1.6f * sin(float(0.2f * pos.x - c.time) + 0.5f) + 1.2f * cos(float(0.2f * pos.z + c.time) - 0.5f));
    pos.y -= 0.05f * (1.3f * cos(float(5.0f * pos.x - 1.1f * c.time) + 0.1f) - 0.9f * sin(float(5.0f * pos.z - 0.7f * c.time) - 0.4f));
    pos.y -= 0.02f * (0.6f * sin(float(8.0f * pos.x - 0.6f * c.time) - 0.6f) + 0.7f * cos(float(8.0f * pos.z - 1.3f * c.time) + 0.7f));
    gl_Position = c.transform * vec4(inPosition.x, pos.y, inPosition.z, 1.0);
    fragColor = inColor;
}