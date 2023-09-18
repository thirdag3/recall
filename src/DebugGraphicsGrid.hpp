#pragma once

#include "VertexArray.hpp"

#include <memory>

#include "Shader.hpp"
#include "Renderer.hpp"

class DebugGraphicsGrid
{
  public:
    DebugGraphicsGrid(int size);
    void Draw(const Renderer& r) const;

  private:
    int m_size;
    VertexArray m_vao;
    std::unique_ptr<VertexBuffer> m_vbo;
    std::unique_ptr<Shader> m_shader;
};
