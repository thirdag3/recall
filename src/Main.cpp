#include <Window.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <memory>
#include <vector>

#include "BufferLayout.hpp"
#include "IndexBuffer.hpp"
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

    struct ViewProjectionMatrix
    {
        glm::mat4 projection;
        glm::mat4 view;
    } viewProjection{};

    UniformBuffer ubo(128, 0);

    Shader s("Assets/Shaders/Basic.vert", "Assets/Shaders/Basic.frag");
    s.Bind();

    Renderer r;

    glm::mat4 transformation(1.0f);
    

    viewProjection.projection =
        glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    viewProjection.view =
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

    ubo.SetData(
        reinterpret_cast<void*>(&viewProjection), sizeof(viewProjection), 0);

    vao.Bind();
    while (!w.ShouldClose()) {
        r.Clear({0.39f, 0.58f, 0.92f, 1.0f});

        transformation = glm::rotate(transformation, 0.03f, glm::vec3(0.0f, 0.2f, 0.0f));
        s.SetUniform("model", transformation);

        r.DrawIndexed(vao);
        w.Update();
    }
}
