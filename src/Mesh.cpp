#include "Mesh.hpp"

#include <glad/glad.h>

Mesh::Mesh(std::unique_ptr<VertexArray> vertexArray, std::shared_ptr<Material> material)
: m_vao(std::move(vertexArray)),
  m_material(material)
{
}

void Mesh::Draw(const Renderer& renderer) const
{
    GLint maxTextureUnits;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxTextureUnits);

    m_material->GetDiffuseTexture().BindToUnit(0);

    GLuint location = glGetUniformLocation(3, "texture1");
    glUniform1i(location, 0);

    renderer.DrawIndexed(DrawingPrimitiveType::Triangles, *m_vao);
}
