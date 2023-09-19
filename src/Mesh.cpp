#include "Mesh.hpp"

Mesh::Mesh(std::unique_ptr<VertexArray> vertexArray) : m_vao(std::move(vertexArray))
{
}

void Mesh::Draw(const Renderer& renderer) const
{
    renderer.DrawIndexed(DrawingPrimitiveType::Triangles, *m_vao);
}
