#pragma once

#include <glm/glm.hpp>

#include "VertexArray.hpp"

class Renderer
{
  public:
    void Draw(const VertexArray& vertexArray, int count);
    void DrawIndexed(const VertexArray& vertexArray);
    void Clear(glm::vec4 color);
};