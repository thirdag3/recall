#pragma once

#include <glm/glm.hpp>

class Material
{
  public:
    glm::vec3 GetAmbientColor();
    glm::vec3 GetDiffuseColor();
    glm::vec3 GetSpecularColor();
    float GetShininess();
    void SetAmbientColor(glm::vec3 ambientColor);
    void SetDiffuseColor(glm::vec3 diffuseColor);
    void SetSpecularColor(glm::vec3 specularColor);
    void SetShininess(float shininess);

  private:
    glm::vec3 m_ambientColor;
    glm::vec3 m_diffuseColor;
    glm::vec3 m_specularColor;
    float m_shininess;
};
