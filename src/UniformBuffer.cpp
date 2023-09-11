#include "UniformBuffer.h"

UniformBuffer::UniformBuffer()
{
    glGenBuffers(1, &m_id);
}

UniformBuffer::~UniformBuffer()
{
    Unbind();
    glDeleteBuffers(1, &m_id);
}

void UniformBuffer::Bind() const
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_id);
}

void UniformBuffer::Unbind() const
{
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
