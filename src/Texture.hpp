#pragma once

#include <glad/glad.h>

#include "Image.hpp"

class Texture
{
  public:
    Texture(const Image& image);
    ~Texture();
    void BindToUnit(unsigned int unit);

  private:
    GLuint m_id;
};
