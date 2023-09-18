#pragma once

#include <glm/glm.hpp>

#include "VertexArray.hpp"

enum class DrawingPrimitiveType
{
    Triangles,
    Lines
};

class Renderer
{
  public:
    Renderer();
    void Draw(DrawingPrimitiveType primitiveType, const VertexArray& vertexArray, int count) const;
    void DrawIndexed(DrawingPrimitiveType primitiveType, const VertexArray& vertexArray) const;
    void Clear(glm::vec4 color) const;
};
