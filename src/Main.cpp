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
#include "PrimitiveFactory.hpp"

int main(int argc, const char** argv)
{
    Window w(800, 600, "RECALL");

    auto cube = PrimitiveFactory::CreateCube(1.0f);
    auto cube2 = PrimitiveFactory::CreateCube(0.5f);
    auto cube3 = PrimitiveFactory::CreateCube(0.5f);

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
    Transform transform2;
    Transform transform3;

    transform2.TranslateX(3.0f);
    transform3.TranslateX(-3.0f);

    DebugGraphicsGrid grid(50, glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));

    while (!w.ShouldClose()) {
        r.Clear({ 0.15f, 0.15f, 0.15f, 1.0f });

        camera.Update();

        auto& vp = camera.GetViewProjectionMatrix();
        ubo.SetData(reinterpret_cast<const void*>(&vp), sizeof(viewProjectionMatrix), 0);

        s.Use();
        s.SetUniform("lightPos", glm::vec3(0.0f, 2.5f, 0.0f));
        s.SetUniform("cameraPos", camera.GetPosition());

        transform.RotateX(0.25f);
        transform.RotateY(0.5f);
        s.SetUniform("model", transform.GetTransformationMatrix());
        cube->Draw(r);

        transform2.RotateZ(3.5f);
        s.SetUniform("model", transform2.GetTransformationMatrix());
        cube2->Draw(r);

        transform3.RotateY(2.5f);
        s.SetUniform("model", transform3.GetTransformationMatrix());
        cube3->Draw(r);

        grid.Draw(r);

        w.Update();
    }
}
