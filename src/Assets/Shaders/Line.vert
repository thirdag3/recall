#version 460 core

layout (location = 0) in vec3 aPos;

layout (std140, binding = 0) uniform Matrices
{
    mat4 projection; // offset = 0
    mat4 view; // offset = 64 ((4 * 4) * 4 = 64)
};

void main()
{
    gl_Position = projection * view * vec4(aPos, 1.0);
}
