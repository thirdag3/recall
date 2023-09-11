#include "Renderer.h"

#include <glad/glad.h>

void Renderer::Draw(const VertexArray& vertexArray, int count)
{
    vertexArray.Bind();
    glDrawArrays(GL_TRIANGLES, 0, count);
}

void Renderer::DrawIndexed(const VertexArray& vertexArray)
{
    vertexArray.Bind();
    glDrawElements(GL_TRIANGLES,
        vertexArray.GetIndexBuffer()->GetCount(),
        GL_UNSIGNED_INT,
        nullptr);
}

void Renderer::Clear(glm::vec4 color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}
