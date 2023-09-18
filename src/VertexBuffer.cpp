#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer(float* vertices, size_t size)
{
    glCreateBuffers(1, &m_id);
    glNamedBufferData(m_id, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_id);
}

const BufferLayout& VertexBuffer::GetLayout() const
{
    return m_layout;
}

void VertexBuffer::SetLayout(const BufferLayout& layout)
{
    m_layout = layout;
}

GLuint VertexBuffer::GetID() const
{
    return m_id;
}
