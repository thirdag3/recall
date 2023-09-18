#include "DebugGraphicsGrid.hpp"

#include <vector>

#include <glad/glad.h>

#include "Vertex.hpp"
#include "BufferLayout.hpp"
#include "VertexBuffer.hpp"

DebugGraphicsGrid::DebugGraphicsGrid(int size)
: m_size(size)
{
    std::vector<Vertex> vertices;

    BufferLayout bufferLayout;
    bufferLayout.PushAttribute<glm::vec3>();

    for (int i = -m_size / 2; i <= m_size / 2; ++i) {
        // First line
        vertices.push_back({{i, 0, -m_size / 2, }});
        vertices.push_back({{i, 0, m_size / 2, }});

        // Second line
        vertices.push_back({{-m_size / 2, 0, i, }});
        vertices.push_back({{m_size / 2, 0, i, }});
    }

    m_vbo =
        std::make_unique<VertexBuffer>(reinterpret_cast<float*>(&vertices[0]),
            sizeof(Vertex) * vertices.size());

    m_vbo->SetLayout(bufferLayout);

    m_shader = std::make_unique<Shader>(
        "Assets/Shaders/Line.vert", "Assets/Shaders/Line.frag");

    m_vao.AddVertexBuffer(*m_vbo);
}

void DebugGraphicsGrid::Draw(const Renderer& r) const
{
    m_vao.Bind();
    m_shader->Use();
    glDrawArrays(GL_LINES, 0, (m_size + 1) * 4);
    m_vao.Unbind();
}
