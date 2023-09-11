#include <Window.hpp>

#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "Shader.hpp"
#include "BufferLayout.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Renderer.hpp"

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

    Shader s("Assets/Shaders/Basic.vert", "Assets/Shaders/Basic.frag");
    s.Bind();

    Renderer r;

    vao.Bind();
    while (!w.ShouldClose()) {
        r.Clear({0.39f, 0.58f, 0.92f, 1.0f});
        r.Draw(vao, triangle.size());
        w.Update();
    }
}
