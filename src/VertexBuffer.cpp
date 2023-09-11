#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer(float* vertices, size_t size)
{
    glGenBuffers(1, &m_id);

    Bind();
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    Unbind();
    glDeleteBuffers(1, &m_id);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

const BufferLayout& VertexBuffer::GetLayout() const
{
    return m_layout;
}

void VertexBuffer::SetLayout(const BufferLayout& layout)
{
    m_layout = layout;
}
