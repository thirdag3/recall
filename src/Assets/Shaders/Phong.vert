#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

layout (std140, binding = 0) uniform Matrices
{
    mat4 projection; // offset = 0
    mat4 view; // offset = 64 ((4 * 4) * 4 = 64)
};

out vec3 normal;
out vec4 fragPos;

uniform mat4 model;

void main()
{
    normal = mat3(transpose(inverse(model))) * aNormal;
    fragPos = model * vec4(aPos, 1.0);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
