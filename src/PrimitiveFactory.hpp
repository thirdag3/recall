#pragma once

#include <memory>

#include "Mesh.hpp"

class PrimitiveFactory
{
  public:
    static std::unique_ptr<Mesh> CreateCube(float size);
};
