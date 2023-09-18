#include "IndexBuffer.hpp"

IndexBuffer::IndexBuffer(GLuint* indices, GLuint count) : m_count(count)
{
    glCreateBuffers(1, &m_id);
    glNamedBufferData(m_id, count * sizeof(GLuint), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_id);
}

GLuint IndexBuffer::GetCount()
{
    return m_count;
}

GLuint IndexBuffer::GetID() const
{
    return m_id;
}
