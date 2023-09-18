#include "Renderer.hpp"

#include <glad/glad.h>

GLenum DrawingPrimitiveTypeToGL(DrawingPrimitiveType primitiveType)
{
    switch (primitiveType) {
    case DrawingPrimitiveType::Triangles:
        return GL_TRIANGLES;

    case DrawingPrimitiveType::Lines:
        return GL_LINES;
    }
}

Renderer::Renderer()
{
    glEnable(GL_DEPTH_TEST);
}

void Renderer::Draw(DrawingPrimitiveType primitiveType, const VertexArray& vertexArray, int count) const
{
    vertexArray.Bind();
    glDrawArrays(DrawingPrimitiveTypeToGL(primitiveType), 0, count);
}

void Renderer::DrawIndexed(DrawingPrimitiveType primitiveType, const VertexArray& vertexArray) const
{
    vertexArray.Bind();
    glDrawElements(
        DrawingPrimitiveTypeToGL(primitiveType), vertexArray.GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear(glm::vec4 color) const
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
