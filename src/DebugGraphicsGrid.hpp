#pragma once

#include "VertexArray.hpp"

#include <memory>

#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Renderer.hpp"

class DebugGraphicsGrid
{
  public:
    DebugGraphicsGrid(int size, glm::vec4 lineColor);
    void Draw(const Renderer& r) const;
    const glm::vec4& GetLineColor() const;
    void SetLineColor(glm::vec4 color);

  private:
    int m_size;
    VertexArray m_vao;
    std::unique_ptr<VertexBuffer> m_vbo;
    std::unique_ptr<Shader> m_shader;
    glm::vec4 m_lineColor;
};
