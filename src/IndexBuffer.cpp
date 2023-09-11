#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(GLuint* indices, GLuint count) : m_count(count)
{
    glGenBuffers(1, &m_id);

    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        count * sizeof(GLuint),
        indices,
        GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    Unbind();
    glDeleteBuffers(1, &m_id);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLuint IndexBuffer::GetCount()
{
    return m_count;
}
