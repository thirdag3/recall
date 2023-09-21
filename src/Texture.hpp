#pragma once

#include <glad/glad.h>

#include "Image.hpp"

class Texture
{
  public:
    Texture(const Image& image);
    Texture(const Texture& other) = delete;
    Texture& operator=(const Texture& other) = delete;
    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;
    ~Texture();
    void BindToUnit(unsigned int unit) const;

  private:
    GLuint m_id;
};
