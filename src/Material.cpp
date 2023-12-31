#include "Material.hpp"

Material::Material(std::shared_ptr<Shader> shader, Texture&& diffuse)
: m_ambientColor(0.0f),
  m_diffuseColor(0.0f),
  m_specularColor(0.0f),
  m_shininess(0.0f),
  m_diffuse(std::move(diffuse)),
  m_shader(shader)
{
}

glm::vec3 Material::GetAmbientColor() const
{
    return m_ambientColor;
}

glm::vec3 Material::GetDiffuseColor() const
{
    return m_diffuseColor;
}

glm::vec3 Material::GetSpecularColor() const
{
    return m_specularColor;
}

const Texture& Material::GetDiffuseTexture() const
{
    return m_diffuse;
}

std::shared_ptr<Shader> Material::GetShader() const
{
    return m_shader;
}

float Material::GetShininess() const
{
    return m_shininess;
}

void Material::SetAmbientColor(glm::vec3 ambientColor)
{
    m_ambientColor = ambientColor;
}

void Material::SetDiffuseColor(glm::vec3 diffuseColor)
{
    m_diffuseColor = diffuseColor;
}

void Material::SetSpecularColor(glm::vec3 specularColor)
{
    m_specularColor = specularColor;
}

void Material::SetShininess(float shininess)
{
    m_shininess = shininess;
}

void Material::SetDiffuseTexture(Texture&& diffuseTexture)
{
    m_diffuse = std::move(diffuseTexture);
}

void Material::SetShader(std::shared_ptr<Shader> shader)
{
    m_shader = shader;
}
