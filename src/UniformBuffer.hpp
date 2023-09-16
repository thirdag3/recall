#pragma once

#include <glad/glad.h>
#include <stddef.h>

class UniformBuffer
{
  public:
    UniformBuffer(size_t size, unsigned int binding);
    UniformBuffer(const UniformBuffer& other) = delete;
    UniformBuffer& operator=(const UniformBuffer& other) = delete;
    UniformBuffer(const UniformBuffer&& other) = delete;
    UniformBuffer& operator=(const UniformBuffer&& other) noexcept = delete;
    ~UniformBuffer();
    void Bind() const;
    void Unbind() const;
    void SetData(const void* data, size_t size, unsigned int offset);

  private:
    GLuint m_id;
};
