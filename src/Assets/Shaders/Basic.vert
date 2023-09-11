#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

layout (std140, binding = 0) uniform Matrices
{
    mat4 projection; // offset = 0
    mat4 view; // offset = 64 ((4 * 4) * 4 = 64)
};

uniform mat4 model;

out vec3 outColor;

void main()
{
    // gl_Position = projection * view * model * vec4(aPos, 1.0);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    outColor = aColor;
}
