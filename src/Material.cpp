#include "Material.hpp"

glm::vec3 Material::GetAmbientColor()
{
    return m_ambientColor;
}

glm::vec3 Material::GetDiffuseColor()
{
    return m_diffuseColor;
}

glm::vec3 Material::GetSpecularColor()
{
    return m_specularColor;
}

float Material::GetShininess()
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
