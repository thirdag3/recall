#pragma once

#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 position;
};

struct VertexPosNormal
{
    glm::vec3 position;
    glm::vec3 normal;
};

struct VertexPosNormalTexture
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
};

struct VertexPosColorNormal
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 normal;
};
