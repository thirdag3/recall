#include "PrimitiveFactory.hpp"

#include "Vertex.hpp"

std::unique_ptr<Mesh> PrimitiveFactory::CreateCube(float size)
{
    std::vector<VertexPosNormal> vertices = {
        // Front face
        { { -size / 2.0f, -size / 2.0f, size / 2.0f }, { 0.0f, 0.0f, 1.0f } },
        { { size / 2.0f, -size / 2.0f, size / 2.0f }, { 0.0f, 0.0f, 1.0f } },
        { { size / 2.0f, size / 2.0f, size / 2.0f }, { 0.0f, 0.0f, 1.0f } },
        { { -size / 2.0f, size / 2.0f, size / 2.0f }, { 0.0f, 0.0f, 1.0f } },

        // Back face
        { { -size / 2.0f, -size / 2.0f, -size / 2.0f }, { 0.0f, 0.0f, -1.0f } },
        { { size / 2.0f, -size / 2.0f, -size / 2.0f }, { 0.0f, 0.0f, -1.0f } },
        { { size / 2.0f, size / 2.0f, -size / 2.0f }, { 0.0f, 0.0f, -1.0f } },
        { { -size / 2.0f, size / 2.0f, -size / 2.0f }, { 0.0f, 0.0f, -1.0f } },

        // Top face
        { { -size / 2.0f, size / 2.0f, size / 2.0f }, { 0.0f, 1.0f, 0.0f } },
        { { size / 2.0f, size / 2.0f, size / 2.0f }, { 0.0f, 1.0f, 0.0f } },
        { { size / 2.0f, size / 2.0f, -size / 2.0f }, { 0.0f, 1.0f, 0.0f } },
        { { -size / 2.0f, size / 2.0f, -size / 2.0f }, { 0.0f, 1.0f, 0.0f } },

        // Bottom face
        { { -size / 2.0f, -size / 2.0f, size / 2.0f }, { 0.0f, -1.0f, 0.0f } },
        { { size / 2.0f, -size / 2.0f, size / 2.0f }, { 0.0f, -1.0f, 0.0f } },
        { { size / 2.0f, -size / 2.0f, -size / 2.0f }, { 0.0f, -1.0f, 0.0f } },
        { { -size / 2.0f, -size / 2.0f, -size / 2.0f }, { 0.0f, -1.0f, 0.0f } },

        // Right face
        { { size / 2.0f, -size / 2.0f, size / 2.0f }, { 1.0f, 0.0f, 0.0f } },
        { { size / 2.0f, -size / 2.0f, -size / 2.0f }, { 1.0f, 0.0f, 0.0f } },
        { { size / 2.0f, size / 2.0f, -size / 2.0f }, { 1.0f, 0.0f, 0.0f } },
        { { size / 2.0f, size / 2.0f, size / 2.0f }, { 1.0f, 0.0f, 0.0f } },

        // Left face
        { { -size / 2.0f, -size / 2.0f, size / 2.0f }, { -1.0f, 0.0f, 0.0f } },
        { { -size / 2.0f, -size / 2.0f, -size / 2.0f }, { -1.0f, 0.0f, 0.0f } },
        { { -size / 2.0f, size / 2.0f, -size / 2.0f }, { -1.0f, 0.0f, 0.0f } },
        { { -size / 2.0f, size / 2.0f, size / 2.0f }, { -1.0f, 0.0f, 0.0f } },
    };

    std::vector<GLuint> indices = { //
        // Front face
        0, 1, 2, 2, 3, 0,

        // Back face
        4, 5, 6, 6, 7, 4,

        // Top face
        8, 9, 10, 10, 11, 8,

        // Bottom face
        12, 13, 14, 14, 15, 12,

        // Right face
        16, 17, 18, 18, 19, 16,

        // Left face
        20, 21, 22, 22, 23, 20
    };

    BufferLayout layout;
    layout.PushAttribute<glm::vec3>();
    layout.PushAttribute<glm::vec3>();

    std::unique_ptr<VertexBuffer> vbo = std::make_unique<VertexBuffer>(
        reinterpret_cast<float*>(&vertices[0]), sizeof(VertexPosNormal) * vertices.size());

    vbo->SetLayout(layout);

    std::unique_ptr<IndexBuffer> ebo = std::make_unique<IndexBuffer>(&indices[0], indices.size());

    std::unique_ptr<VertexArray> vao = std::make_unique<VertexArray>();
    vao->AddVertexBuffer(*vbo);
    vao->SetIndexBuffer(std::move(ebo));

    return std::make_unique<Mesh>(std::move(vao), nullptr);
}
