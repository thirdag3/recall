#include <Window.hpp>

#include <iostream>
#include <memory>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "BufferLayout.hpp"
#include "Camera.hpp"
#include "DebugGraphicsGrid.hpp"
#include "EventDispatcher.hpp"
#include "IEvent.hpp"
#include "IndexBuffer.hpp"
#include "MouseMovedEvent.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Transform.hpp"
#include "UniformBuffer.hpp"
#include "Vertex.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

std::vector<VertexPosColorNormal> CreateCube(float size)
{
    std::vector<VertexPosColorNormal> vertices = {
        // Front face
        { { -size / 2.0f, -size / 2.0f, size / 2.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } },
        { { size / 2.0f, -size / 2.0f, size / 2.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } },
        { { size / 2.0f, size / 2.0f, size / 2.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } },
        { { -size / 2.0f, size / 2.0f, size / 2.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } },

        // Back face
        { { -size / 2.0f, -size / 2.0f, -size / 2.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -1.0f } },
        { { size / 2.0f, -size / 2.0f, -size / 2.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f } },
        { { size / 2.0f, size / 2.0f, -size / 2.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, -1.0f } },
        { { -size / 2.0f, size / 2.0f, -size / 2.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f } },

        // Top face
        { { -size / 2.0f, size / 2.0f, size / 2.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } },
        { { size / 2.0f, size / 2.0f, size / 2.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } },
        { { size / 2.0f, size / 2.0f, -size / 2.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f } },
        { { -size / 2.0f, size / 2.0f, -size / 2.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f } },

        // Bottom face
        { { -size / 2.0f, -size / 2.0f, size / 2.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, -1.0f, 0.0f } },
        { { size / 2.0f, -size / 2.0f, size / 2.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f } },
        { { size / 2.0f, -size / 2.0f, -size / 2.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, -1.0f, 0.0f } },
        { { -size / 2.0f, -size / 2.0f, -size / 2.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f } },

        // Right face
        { { size / 2.0f, -size / 2.0f, size / 2.0f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } },
        { { size / 2.0f, -size / 2.0f, -size / 2.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } },
        { { size / 2.0f, size / 2.0f, -size / 2.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f } },
        { { size / 2.0f, size / 2.0f, size / 2.0f }, { 1.0f, 1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } },

        // Left face
        { { -size / 2.0f, -size / 2.0f, size / 2.0f }, { 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } },
        { { -size / 2.0f, -size / 2.0f, -size / 2.0f }, { 0.0f, 1.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } },
        { { -size / 2.0f, size / 2.0f, -size / 2.0f }, { 0.0f, 0.0f, 1.0f }, { -1.0f, 0.0f, 0.0f } },
        { { -size / 2.0f, size / 2.0f, size / 2.0f }, { 1.0f, 1.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } },
    };

    return vertices;
}

int main(int argc, const char** argv)
{
    Window w(800, 600, "RECALL");

    BufferLayout layout;
    layout.PushAttribute<glm::vec3>();
    layout.PushAttribute<glm::vec3>();
    layout.PushAttribute<glm::vec3>();

    auto triangle = CreateCube(1.0f);
    VertexBuffer vbo(reinterpret_cast<float*>(&triangle[0]), sizeof(VertexPosColorNormal) * triangle.size());

    vbo.SetLayout(layout);

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

    std::unique_ptr<IndexBuffer> ebo = std::make_unique<IndexBuffer>(&indices[0], indices.size());

    VertexArray vao;
    vao.AddVertexBuffer(vbo);
    vao.SetIndexBuffer(std::move(ebo));

    UniformBuffer ubo(sizeof(ViewProjectionMatrix), 0);

    Shader s("Assets/Shaders/Phong.vert", "Assets/Shaders/Phong.frag");
    s.Use();

    Camera camera(45.0f, 0.1f, 100.0f, glm::vec3(-5.0f, 1.0f, 0.0f), w, w);
    Renderer r;

    auto& viewProjectionMatrix = camera.GetViewProjectionMatrix();
    ubo.SetData(reinterpret_cast<const void*>(&viewProjectionMatrix), sizeof(viewProjectionMatrix), 0);

    w.GetEventDispatcher().AddListener([&camera, &ubo](const IEvent& ev) {
        if (const MouseMovedEvent* mouseMovedEvent = dynamic_cast<const MouseMovedEvent*>(&ev)) {
            camera.OnMouseMoved(mouseMovedEvent->GetX(), mouseMovedEvent->GetY());
        }
    });

    Transform transform;

    DebugGraphicsGrid grid(50, glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));

    while (!w.ShouldClose()) {
        r.Clear({ 0.15f, 0.15f, 0.15f, 1.0f });

        camera.Update();

        auto& vp = camera.GetViewProjectionMatrix();

        ubo.SetData(reinterpret_cast<const void*>(&vp), sizeof(viewProjectionMatrix), 0);

        transform.RotateX(0.25f);
        transform.RotateY(0.5f);

        s.Use();
        s.SetUniform("model", transform.GetTransformationMatrix());
        s.SetUniform("lightPos", glm::vec3(1.0f));
        s.SetUniform("cameraPos", camera.GetPosition());
        r.DrawIndexed(DrawingPrimitiveType::Triangles, vao);

        grid.Draw(r);

        w.Update();
    }
}
