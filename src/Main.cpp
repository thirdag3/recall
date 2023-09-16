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

std::vector<Vertex> CreateTriangle(float size)
{
    std::vector<Vertex> vertices = {
        { {-size / 2.0f, -size / 2.0f, size / 2.0f}, {1.0f, 0.0f, 0.0f}},
        {  {size / 2.0f, -size / 2.0f, size / 2.0f}, {0.0f, 1.0f, 0.0f}},
        {   {size / 2.0f, size / 2.0f, size / 2.0f}, {0.0f, 0.0f, 1.0f}},
        {  {-size / 2.0f, size / 2.0f, size / 2.0f}, {0.0f, 0.0f, 1.0f}},
        {{-size / 2.0f, -size / 2.0f, -size / 2.0f}, {0.0f, 0.0f, 1.0f}},
        { {size / 2.0f, -size / 2.0f, -size / 2.0f}, {0.0f, 0.0f, 1.0f}},
        {  {size / 2.0f, size / 2.0f, -size / 2.0f}, {1.0f, 1.0f, 1.0f}},
        { {-size / 2.0f, size / 2.0f, -size / 2.0f}, {0.0f, 0.0f, 1.0f}}
    };

    return vertices;
}

int main(int argc, const char** argv)
{
    Window w(800, 600, "RECALL");

    BufferLayout layout;
    layout.PushAttribute<glm::vec3>();
    layout.PushAttribute<glm::vec3>();

    auto triangle = CreateTriangle(1.0f);
    VertexBuffer vbo(reinterpret_cast<float*>(&triangle[0]),
        sizeof(Vertex) * triangle.size());

    vbo.SetLayout(layout);

    std::vector<GLuint> indices = {0,
        1,
        2,
        2,
        3,
        0,
        3,
        2,
        6,
        6,
        7,
        3,
        7,
        6,
        5,
        5,
        4,
        7,
        4,
        0,
        3,
        3,
        7,
        4,
        0,
        1,
        5,
        5,
        4,
        0,
        1,
        5,
        6,
        6,
        2,
        1};
    std::unique_ptr<IndexBuffer> ebo =
        std::make_unique<IndexBuffer>(&indices[0], indices.size());

    VertexArray vao;
    vao.AddVertexBuffer(vbo);
    vao.SetIndexBuffer(std::move(ebo));

    UniformBuffer ubo(sizeof(ViewProjectionMatrix), 0);

    Shader s("Assets/Shaders/Phong.vert", "Assets/Shaders/Phong.frag");
    s.Bind();

    Camera camera(45.0f, 0.1f, 100.0f, glm::vec3(0.0f, 0.0f, 10.0f), w, w);
    Renderer r;

    auto& viewProjectionMatrix = camera.GetViewProjectionMatrix();
    ubo.SetData(reinterpret_cast<const void*>(&viewProjectionMatrix),
        sizeof(viewProjectionMatrix),
        0);

    w.GetEventDispatcher().AddListener([&camera, &ubo](const IEvent& ev) {
        if (const MouseMovedEvent* mouseMovedEvent =
                dynamic_cast<const MouseMovedEvent*>(&ev))
        {
            camera.OnMouseMoved(
                mouseMovedEvent->GetX(), mouseMovedEvent->GetY());
        }
    });

    Transform transform;

    DebugGraphicsGrid grid(10, 10);

    while (!w.ShouldClose()) {
        r.Clear({0.15f, 0.15f, 0.15f, 1.0f});

        camera.Update();

        auto& vp = camera.GetViewProjectionMatrix();

        ubo.SetData(reinterpret_cast<const void*>(&vp),
            sizeof(viewProjectionMatrix),
            0);

        transform.RotateX(0.5f);
        transform.RotateY(1.0f);

        s.Bind();
        s.SetUniform("model", transform.GetTransformationMatrix());
        r.DrawIndexed(vao);

        grid.Draw(r);

        w.Update();
    }
}
