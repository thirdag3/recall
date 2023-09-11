#include "UniformBuffer.hpp"

UniformBuffer::UniformBuffer(size_t size, unsigned int binding)
{
    glGenBuffers(1, &m_id);

    Bind();
    glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_id);
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

void UniformBuffer::SetData(const void* data, size_t size, unsigned int offset)
{
    Bind();
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
}
