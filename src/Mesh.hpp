#pragma once

#include <memory>

#include "VertexArray.hpp"
#include "Material.hpp"

class Mesh
{
  public:

  private:
    VertexArray m_vao;
    const Material& m_material;
};
