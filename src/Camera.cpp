#include "Camera.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

Camera::Camera(float fov,
    float zNear,
    float zFar,
    const glm::vec3& position,
    const ICameraContext& cameraContext)
: m_fov(fov),
  m_aspect(static_cast<float>(cameraContext.GetWidth()) / cameraContext.GetHeight()),
  m_zNear(zNear),
  m_zFar(zFar),
  m_position(position),
  m_cameraContext(cameraContext)
{
    m_projection = glm::perspective(glm::radians(fov), m_aspect, zNear, zFar);

    m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    m_right = glm::normalize(glm::cross(m_up, position));
    m_forward = glm::vec3(0.0f, 0.0f, -1.0f);

    // m_view = glm::lookAt(position, position + m_forward, m_up);
    m_view = glm::translate(glm::mat4(1.0f), position);

    m_viewProjectionMatrix = {};
    m_viewProjectionMatrix.projection = m_projection;
    m_viewProjectionMatrix.view = m_view;

    cameraContext.SetLockCursor(true);
}

const glm::vec3 Camera::GetForward() const
{
    return m_forward;
}

const glm::vec3 Camera::GetRight() const
{
    return m_right;
}

const glm::mat4& Camera::GetProjectionMatrix() const
{
    return m_projection;
}

const glm::mat4& Camera::GetViewMatrix()
{
    m_view = glm::lookAt(m_position, m_position + m_forward, m_up);
    return m_view;
}

const glm::vec3& Camera::GetPosition() const
{
    return m_position;
}

void Camera::SetPosition(const glm::vec3& position)
{
    m_position = position;
}

void Camera::SetAspectRatio(const float aspect)
{
    m_aspect = aspect;
    m_projection =
        glm::perspective(glm::radians(m_fov), aspect, m_zNear, m_zFar);
}

const ViewProjectionMatrix& Camera::GetViewProjectionMatrix() const
{
    return m_viewProjectionMatrix;
}

void Camera::SetLockCursor(bool shouldLock) const
{
    m_cameraContext.SetLockCursor(shouldLock);
}
