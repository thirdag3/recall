#include "VertexArray.hpp"

#include "BufferLayout.hpp"

VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &m_id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_id);
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_id);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const VertexBuffer& vertexBuffer) const
{
    BufferLayout layout = vertexBuffer.GetLayout();
    GLsizei stride = layout.GetStride();

    GLuint index = 0;
    GLuint offset = 0;
    for (const auto& attribute : layout.GetAttributes()) {
        glEnableVertexArrayAttrib(m_id, index);
        glVertexArrayAttribBinding(m_id, index, 0);
        glVertexArrayAttribFormat(m_id, index, attribute.count, attribute.type, GL_FALSE, offset);

        index++;
        offset += attribute.size;
    }

    glVertexArrayVertexBuffer(m_id, 0, vertexBuffer.GetID(), 0, stride);
}

const std::unique_ptr<IndexBuffer>& VertexArray::GetIndexBuffer() const
{
    return m_indexBuffer;
}

void VertexArray::SetIndexBuffer(std::unique_ptr<IndexBuffer> indexBuffer)
{
    glVertexArrayElementBuffer(m_id, indexBuffer->GetID());
    m_indexBuffer = std::move(indexBuffer);
}
