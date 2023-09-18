#include "Renderer.hpp"

#include <glad/glad.h>

Renderer::Renderer()
{
    glEnable(GL_DEPTH_TEST);
}

void Renderer::Draw(const VertexArray& vertexArray, int count) const
{
    vertexArray.Bind();
    glDrawArrays(GL_TRIANGLES, 0, count);
    vertexArray.Unbind();
}

void Renderer::DrawIndexed(const VertexArray& vertexArray) const
{
    vertexArray.Bind();
    glDrawElements(GL_TRIANGLES,
        vertexArray.GetIndexBuffer()->GetCount(),
        GL_UNSIGNED_INT,
        nullptr);
}

void Renderer::Clear(glm::vec4 color) const
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
