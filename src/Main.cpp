#include <Window.hpp>

#include <iostream>
#include <memory>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "BufferLayout.hpp"
#include "Camera.hpp"
#include "EventDispatcher.hpp"
#include "IEvent.hpp"
#include "IndexBuffer.hpp"
#include "MouseMovedEvent.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "UniformBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
};

std::vector<Vertex> CreateTriangle(float size)
{
    std::vector<Vertex> vertices = {
        {{-size / 2.0f, -size / 2.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {         {0.0f, size / 2.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        { {size / 2.0f, -size / 2.0f, 0.0f}, {0.0f, 0.0f, 1.0f}}
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

    std::vector<GLuint> indices = {0, 1, 2};
    std::unique_ptr<IndexBuffer> ebo =
        std::make_unique<IndexBuffer>(&indices[0], indices.size());

    VertexArray vao;
    vao.AddVertexBuffer(vbo);
    vao.SetIndexBuffer(std::move(ebo));

    UniformBuffer ubo(sizeof(ViewProjectionMatrix), 0);

    Shader s("Assets/Shaders/Basic.vert", "Assets/Shaders/Basic.frag");
    s.Bind();

    Camera camera(45.0f, 0.1f, 100.0f, glm::vec3(0.0f, 0.0f, 10.0f), w);
    Renderer r;

    auto viewProjectionMatrix = camera.GetViewProjectionMatrix();
    ubo.SetData(reinterpret_cast<void*>(&viewProjectionMatrix),
        sizeof(viewProjectionMatrix),
        0);

    glm::mat4 transformation(1.0f);

    w.GetEventDispatcher().AddListener([&camera, &ubo](const IEvent& ev) {
        const std::string& name = ev.GetName();
        std::cout << "Event: " << name;

        if (const MouseMovedEvent* mouseMovedEvent =
                dynamic_cast<const MouseMovedEvent*>(&ev))
        {
            std::cout << " | X: " << mouseMovedEvent->GetX()
                      << " | Y: " << mouseMovedEvent->GetY();

            camera.OnMouseMoved(
                mouseMovedEvent->GetX(), mouseMovedEvent->GetY());

            auto& vp = camera.GetViewProjectionMatrix();

            ubo.SetData(reinterpret_cast<const void*>(&vp),
                sizeof(viewProjectionMatrix),
                0);
        }

        std::cout << std::endl;
    });

    vao.Bind();
    while (!w.ShouldClose()) {
        r.Clear({0.39f, 0.58f, 0.92f, 1.0f});

        transformation =
            glm::rotate(transformation, 0.03f, glm::vec3(0.0f, 0.2f, 0.0f));
        s.SetUniform("model", transformation);

        r.DrawIndexed(vao);
        w.Update();
    }
}
