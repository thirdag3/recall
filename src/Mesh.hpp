#pragma once

#include <memory>

#include "Material.hpp"
#include "VertexArray.hpp"

class Mesh
{
  public:
    Mesh();

  private:
    VertexArray m_vao;
    const Material& m_material;
};
