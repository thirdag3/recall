#pragma once

#include <glm/glm.hpp>

class Transform
{
  public:
    Transform();
    void TranslateX(float x);
    void TranslateY(float y);
    void TranslateZ(float z);
    void RotateX(float angle);
    void RotateY(float angle);
    void RotateZ(float angle);
    void ScaleX(float x);
    void ScaleY(float y);
    void ScaleZ(float z);
    const glm::vec3& GetPosition() const;
    const glm::vec3& GetRotation() const;
    const glm::vec3& GetScale() const;
    void SetPosition(const glm::vec3& position);
    void SetRotation(const glm::vec3& rotation);
    void SetScale(const glm::vec3& scale);
    glm::mat4 GetTransformationMatrix() const;

  private:
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
};
