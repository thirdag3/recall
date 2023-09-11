#pragma once

#include <glm/glm.hpp>

struct ViewProjectionMatrix
{
    glm::mat4 projection;
    glm::mat4 view;
};

class Camera
{
  public:
    Camera(float fov,
        float aspect,
        float zNear,
        float zFar,
        const glm::vec3& position);
    const glm::vec3 GetForward() const;
    const glm::vec3 GetRight() const;
    const glm::mat4& GetProjectionMatrix() const;
    const glm::mat4& GetViewMatrix();
    const glm::vec3& GetPosition() const;
    void SetPosition(const glm::vec3& position);
    void SetAspectRatio(const float aspect);
    const ViewProjectionMatrix& GetViewProjectionMatrix() const;

  private:
    float m_fov;
    float m_aspect;
    float m_zNear;
    float m_zFar;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_forward;
    glm::vec3 m_position;
    glm::mat4 m_projection;
    glm::mat4 m_view;
    ViewProjectionMatrix m_viewProjectionMatrix;
};
