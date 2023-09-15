#pragma once

#include <glm/glm.hpp>

#include "VertexArray.hpp"

class Renderer
{
  public:
    Renderer();
    void Draw(const VertexArray& vertexArray, int count) const;
    void DrawIndexed(const VertexArray& vertexArray) const;
    void Clear(glm::vec4 color) const;
};
