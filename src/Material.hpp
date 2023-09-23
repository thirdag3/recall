#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "Texture.hpp"
#include "Shader.hpp"

class Material
{
  public:
    Material(std::shared_ptr<Shader> shader, Texture&& diffuse);
    glm::vec3 GetAmbientColor() const;
    glm::vec3 GetDiffuseColor() const;
    glm::vec3 GetSpecularColor() const;
    float GetShininess() const;
    const Texture& GetDiffuseTexture() const;
    std::shared_ptr<Shader> GetShader() const;
    void SetAmbientColor(glm::vec3 ambientColor);
    void SetDiffuseColor(glm::vec3 diffuseColor);
    void SetSpecularColor(glm::vec3 specularColor);
    void SetShininess(float shininess);
    void SetDiffuseTexture(Texture&& diffuseTexture);
    void SetShader(std::shared_ptr<Shader> shader);

  private:
    glm::vec3 m_ambientColor;
    glm::vec3 m_diffuseColor;
    glm::vec3 m_specularColor;
    float m_shininess;
    Texture m_diffuse;
    std::shared_ptr<Shader> m_shader;
};
