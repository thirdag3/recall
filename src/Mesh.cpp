#include "Mesh.hpp"

#include <glad/glad.h>

Mesh::Mesh(std::unique_ptr<VertexArray> vertexArray, std::shared_ptr<Material> material)
: m_vao(std::move(vertexArray)),
  m_material(material)
{
}

void Mesh::Draw(const Renderer& renderer) const
{
    m_material->GetDiffuseTexture().BindToUnit(0);
    m_material->GetShader()->SetUniform("texture_diffuse", 0);

    renderer.DrawIndexed(DrawingPrimitiveType::Triangles, *m_vao);
}
