#pragma once

#include <glad/glad.h>

class IndexBuffer
{
  public:
    IndexBuffer(GLuint* indices, GLuint count);
    IndexBuffer(const IndexBuffer& other) = delete;
    IndexBuffer& operator=(const IndexBuffer& other) = delete;
    IndexBuffer(const IndexBuffer&& other) = delete;
    IndexBuffer& operator=(const IndexBuffer&& other) noexcept = delete;
    ~IndexBuffer();
    GLuint GetCount();
    GLuint GetID() const;

  private:
    GLuint m_id;
    GLuint m_count;
};
