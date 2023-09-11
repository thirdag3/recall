#pragma once

#include <memory>
#include <vector>
#include <glad/glad.h>

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

class VertexArray
{
  public:
    VertexArray();
    VertexArray(const VertexArray& other) = delete;
    VertexArray& operator=(const VertexArray& other) = delete;
    VertexArray(VertexArray&& other) = delete;
    VertexArray& operator=(VertexArray&& other) = delete;
    ~VertexArray();
    void Bind() const;
    void Unbind() const;
    void AddVertexBuffer(const VertexBuffer& vertexBuffer) const;
    const std::unique_ptr<IndexBuffer>& GetIndexBuffer() const;
    void SetIndexBuffer(std::unique_ptr<IndexBuffer> indexBuffer);

  private:
    GLuint m_id;
    std::unique_ptr<IndexBuffer> m_indexBuffer;
};
