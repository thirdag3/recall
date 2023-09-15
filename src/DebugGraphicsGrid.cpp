#include "DebugGraphicsGrid.hpp"

#include <vector>

#include <glad/glad.h>

#include "Vertex.hpp"
#include "BufferLayout.hpp"
#include "VertexBuffer.hpp"

DebugGraphicsGrid::DebugGraphicsGrid(int width, int height)
: m_width(width),
  m_height(height)
{
    std::vector<Vertex> vertices;

    BufferLayout bufferLayout;
    bufferLayout.PushAttribute<glm::vec3>();
    bufferLayout.PushAttribute<glm::vec3>();

    for (int i = -10; i <= 10; ++i) {
        // First line
        vertices.push_back({{i, 0, -10, }, {1.0f, 1.0f, 1.0f}});
        vertices.push_back({{i, 0, 10, }, {1.0f, 1.0f, 1.0f}});

        // Second line
        vertices.push_back({{-10, 0, i, }, {1.0f, 1.0f, 1.0f}});
        vertices.push_back({{10, 0, i, }, {1.0f, 1.0f, 1.0f}});
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
    m_shader->Bind();
    glDrawArrays(GL_LINES, 0, 84);
    m_shader->Unbind();
}
