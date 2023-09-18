#pragma once

#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
};

struct VertexPosNormal
{
    glm::vec3 position;
    glm::vec3 normal;
};

struct VertexPosColorNormal
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 normal;
};
