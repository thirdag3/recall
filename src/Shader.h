#pragma once

#include <string>

#include <glm/glm.hpp>
#include <glad/glad.h>

class Shader
{
  public:
    Shader(const std::string& vertexShaderPath,
        const std::string& fragmentShaderPath);
    Shader(const Shader& other) = delete;
    Shader& operator=(const Shader& other) = delete;
    Shader(const Shader&& other) = delete;
    Shader& operator=(const Shader&& other) noexcept = delete;
    ~Shader();
    void Bind() const;
    void Unbind() const;
    void SetUniform(const std::string& name, const int& value) const;
    void SetUniform(const std::string& name, const float& value) const;
    void SetUniform(const std::string& name, const glm::vec2& vector) const;
    void SetUniform(const std::string& name, const glm::vec3& vector) const;
    void SetUniform(const std::string& name, const glm::vec4& vector) const;
    void SetUniform(const std::string& name, const glm::mat3& matrix) const;
    void SetUniform(const std::string& name, const glm::mat4& matrix) const;

  private:
    GLuint m_id;
};
