#include "Camera.hpp"

#include <iostream>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

Camera::Camera(float fov,
    float zNear,
    float zFar,
    const glm::vec3& position,
    const ICameraContext& cameraContext,
    const IInputContext& inputContext)
: m_fov(fov),
  m_aspect(static_cast<float>(cameraContext.GetWidth()) / cameraContext.GetHeight()),
  m_zNear(zNear),
  m_zFar(zFar),
  m_position(position),
  m_cameraContext(cameraContext),
  m_inputContext(inputContext)
{
    m_projection = glm::perspective(glm::radians(m_fov), m_aspect, m_zNear, m_zFar);

    m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    m_forward = glm::vec3(0.0f, 0.0f, -1.0f);

    m_view = glm::lookAt(m_position, m_position + m_forward, m_up);

    m_right = glm::normalize(glm::cross(m_forward, m_up));
    m_up = glm::cross(m_right, m_forward);

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
    m_projection = glm::perspective(glm::radians(m_fov), aspect, m_zNear, m_zFar);
}

const ViewProjectionMatrix& Camera::GetViewProjectionMatrix() const
{
    return m_viewProjectionMatrix;
}

void Camera::SetLockCursor(bool shouldLock) const
{
    m_cameraContext.SetLockCursor(shouldLock);
}

void Camera::OnMouseMoved(float x, float y)
{
    if (m_isFirstLookAround) {
        m_lastX = x;
        m_lastY = y;
        m_isFirstLookAround = false;
    }

    float offsetX = (x - m_lastX);
    float offsetY = (m_lastY - y);

    offsetX *= m_sensitivity;
    offsetY *= m_sensitivity;

    m_lastX = x;
    m_lastY = y;

    m_yaw += offsetX;
    m_pitch += offsetY;

    if (m_pitch > 89.0f) {
        m_pitch = 89.0f;
    }

    if (m_pitch < -89.0f) {
        m_pitch = -89.0f;
    }

    glm::vec3 direction(0.0f);
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    m_forward = glm::normalize(direction);
    m_right = glm::normalize(glm::cross(m_forward, glm::vec3(0.0f, 1.0f, 0.0f)));
    m_up = glm::cross(m_right, m_forward);
}

void Camera::Update()
{
    float currentMoveSpeed = m_moveSpeed;

    if (m_inputContext.IsKeyPressed(KeyCode::LeftShift)) {
        m_moveSpeed *= 2.0f;
    }

    if (m_inputContext.IsKeyPressed(KeyCode::W)) {
        m_position += m_forward * m_moveSpeed;
    }

    if (m_inputContext.IsKeyPressed(KeyCode::A)) {
        m_position -= m_right * m_moveSpeed;
    }

    if (m_inputContext.IsKeyPressed(KeyCode::S)) {
        m_position -= m_forward * m_moveSpeed;
    }

    if (m_inputContext.IsKeyPressed(KeyCode::D)) {
        m_position += m_right * m_moveSpeed;
    }

    if (m_inputContext.IsKeyPressed(KeyCode::Space)) {
        m_position += glm::vec3(0.0f, 1.0f, 0.0f) * m_moveSpeed;
    }

    if (m_inputContext.IsKeyPressed(KeyCode::LeftControl)) {
        m_position -= glm::vec3(0.0f, 1.0f, 0.0f) * m_moveSpeed;
    }

    m_moveSpeed = currentMoveSpeed;

    UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
    m_view = glm::lookAt(m_position, m_position + m_forward, m_up);
    m_viewProjectionMatrix.view = m_view;
}
