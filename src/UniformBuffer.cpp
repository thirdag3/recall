#include "UniformBuffer.hpp"

UniformBuffer::UniformBuffer(size_t size, unsigned int binding)
{
    glCreateBuffers(1, &m_id);
    glNamedBufferData(m_id, size, nullptr, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_id);
}

UniformBuffer::~UniformBuffer()
{
    glDeleteBuffers(1, &m_id);
}

void UniformBuffer::SetData(const void* data, size_t size, unsigned int offset)
{
    glNamedBufferSubData(m_id, offset, size, data);
}
