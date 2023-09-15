#include "Transform.hpp"

#include <glm/ext/matrix_transform.hpp>

Transform::Transform()
{
    m_position = glm::vec3(1.0f);
    m_rotation = glm::vec3(1.0f);
    m_scale = glm::vec3(1.0f);
}

void Transform::RotateX(float angle)
{
    m_rotation.x += angle;
}

void Transform::RotateY(float angle)
{
    m_rotation.y += angle;
}

void Transform::RotateZ(float angle)
{
    m_rotation.z += angle;
}

const glm::vec3& Transform::GetPosition() const
{
    return m_position;
}

const glm::vec3& Transform::GetRotation() const
{
    return m_rotation;
}

const glm::vec3& Transform::GetScale() const
{
    return m_scale;
}

void Transform::SetPosition(const glm::vec3& position)
{
    m_position = position;
}

void Transform::SetRotation(const glm::vec3& rotation)
{
    m_rotation = rotation;
}

void Transform::SetScale(const glm::vec3& scale)
{
    m_scale = scale;
}

glm::mat4 Transform::GetTransformationMatrix() const
{
    glm::mat4 transform = glm::mat4(1.0f);

    transform = glm::translate(transform, m_position);

    transform = glm::rotate(
        transform, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

    transform = glm::rotate(
        transform, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));

    transform = glm::rotate(
        transform, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    transform = glm::scale(transform, m_scale);

    return transform;
}
