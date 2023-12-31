#pragma once

#include <glad/glad.h>

#include "BufferLayout.hpp"

class VertexBuffer
{
  public:
    VertexBuffer(float* vertices, size_t size);
    VertexBuffer(const VertexBuffer& other) = delete;
    VertexBuffer& operator=(const VertexBuffer& other) = delete;
    VertexBuffer(const VertexBuffer&& other) = delete;
    VertexBuffer& operator=(const VertexBuffer&& other) noexcept = delete;
    ~VertexBuffer();
    const BufferLayout& GetLayout() const;
    void SetLayout(const BufferLayout& layout);
    GLuint GetID() const;

  private:
    GLuint m_id;
    BufferLayout m_layout;
};
