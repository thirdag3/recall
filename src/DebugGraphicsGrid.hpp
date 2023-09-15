#pragma once

#include "VertexArray.hpp"

#include <memory>

#include "Shader.hpp"
#include "Renderer.hpp"

class DebugGraphicsGrid
{
  public:
    DebugGraphicsGrid(int width, int height);
    void Draw(const Renderer& r) const;

  private:
    int m_width;
    int m_height;
    VertexArray m_vao;
    std::unique_ptr<VertexBuffer> m_vbo;
    std::unique_ptr<Shader> m_shader;
};
