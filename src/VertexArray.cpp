#include "VertexArray.hpp"

#include "BufferLayout.hpp"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_id);
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
    Bind();
    vertexBuffer.Bind();

    BufferLayout layout = vertexBuffer.GetLayout();

    unsigned int stride = layout.GetStride();

    unsigned int index = 0;
    unsigned int offset = 0;
    for (const auto& attribute : layout.GetAttributes()) {
        glVertexAttribPointer(index,
            attribute.count,
            attribute.type,
            GL_FALSE,
            stride,
            reinterpret_cast<void*>(offset));
        glEnableVertexAttribArray(index);

        index++;
        offset += attribute.size;
    }
}

const std::unique_ptr<IndexBuffer>& VertexArray::GetIndexBuffer() const
{
    return m_indexBuffer;
}

void VertexArray::SetIndexBuffer(std::unique_ptr<IndexBuffer> indexBuffer)
{
    m_indexBuffer = std::move(indexBuffer);

    Bind();
    m_indexBuffer->Bind();
}
