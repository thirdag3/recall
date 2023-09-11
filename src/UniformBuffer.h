#pragma once

#include <glad/glad.h>

class UniformBuffer
{
  public:
    UniformBuffer();
    UniformBuffer(const UniformBuffer& other) = delete;
    UniformBuffer& operator=(const UniformBuffer& other) = delete;
    UniformBuffer(const UniformBuffer&& other) = delete;
    UniformBuffer& operator=(const UniformBuffer&& other) noexcept = delete;
    ~UniformBuffer();
    void Bind() const;
    void Unbind() const;

  private:
    GLuint m_id;
};
