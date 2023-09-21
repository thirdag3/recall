#pragma once

#include <glm/glm.hpp>

#include "Texture.hpp"

class Material
{
  public:
    Material(Texture&& diffuse);
    glm::vec3 GetAmbientColor() const;
    glm::vec3 GetDiffuseColor() const;
    glm::vec3 GetSpecularColor() const;
    const Texture& GetDiffuseTexture() const;
    float GetShininess() const;
    void SetAmbientColor(glm::vec3 ambientColor);
    void SetDiffuseColor(glm::vec3 diffuseColor);
    void SetSpecularColor(glm::vec3 specularColor);
    void SetShininess(float shininess);
    void SetDiffuseTexture(Texture&& diffuseTexture);

  private:
    glm::vec3 m_ambientColor;
    glm::vec3 m_diffuseColor;
    glm::vec3 m_specularColor;
    float m_shininess;
    Texture m_diffuse;
};
