#pragma once

#include <memory>

#include "Material.hpp"
#include "VertexArray.hpp"
#include "Renderer.hpp"

class Mesh
{
  public:
    Mesh(std::unique_ptr<VertexArray> vertexArray, std::shared_ptr<Material> material);
    void Draw(const Renderer& renderer) const;

  private:
    std::unique_ptr<VertexArray> m_vao;
    std::shared_ptr<Material> m_material = nullptr;
};
