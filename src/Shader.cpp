#include "Shader.h"

#include <filesystem>
#include <fstream>

Shader::Shader(const std::string& vertexShaderPath,
    const std::string& fragmentShaderPath)
{
    auto vertexPath = std::filesystem::path(vertexShaderPath);
    auto fragmentPath = std::filesystem::path(fragmentShaderPath);

    if (!std::filesystem::exists(vertexPath)
        || !std::filesystem::exists(fragmentPath))
    {
    }

    auto vertexFileSize = std::filesystem::file_size(vertexPath);
    auto fragmentFileSize = std::filesystem::file_size(fragmentPath);

    std::string vertexShaderSource(vertexFileSize, '\0');
    std::string fragmentShaderSource(fragmentFileSize, '\0');

    std::ifstream vertexFile(vertexPath, std::ios::in | std::ios::binary);
    vertexFile.read(&vertexShaderSource[0], vertexFileSize);
    vertexFile.close();

    std::ifstream fragmentFile(fragmentPath, std::ios::in | std::ios::binary);
    fragmentFile.read(&fragmentShaderSource[0], fragmentFileSize);
    fragmentFile.close();

    const char* vertexShaderSourceBuf = vertexShaderSource.c_str();
    const char* fragmentShaderSourceBuf = fragmentShaderSource.c_str();

    const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSourceBuf, nullptr);
    glCompileShader(vertexShader);

    const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSourceBuf, nullptr);
    glCompileShader(fragmentShader);

    m_id = glCreateProgram();

    glAttachShader(m_id, vertexShader);
    glAttachShader(m_id, fragmentShader);
    glLinkProgram(m_id);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    Unbind();
    glDeleteProgram(m_id);
}

void Shader::Bind() const
{
    glUseProgram(m_id);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetUniform(const std::string& name, const int& value) const
{
    auto location = glGetUniformLocation(m_id, name.c_str());
    glUniform1i(location, value);
}

void Shader::SetUniform(const std::string& name, const float& value) const
{
    auto location = glGetUniformLocation(m_id, name.c_str());
    glUniform1f(location, value);
}

void Shader::SetUniform(const std::string& name, const glm::vec2& vec) const
{
    auto location = glGetUniformLocation(m_id, name.c_str());
    glUniform2f(location, vec[0], vec[1]);
}

void Shader::SetUniform(const std::string& name, const glm::vec3& vec) const
{
    auto location = glGetUniformLocation(m_id, name.c_str());
    glUniform3f(location, vec[0], vec[1], vec[2]);
}

void Shader::SetUniform(const std::string& name, const glm::vec4& vec) const
{
    auto location = glGetUniformLocation(m_id, name.c_str());
    glUniform4f(location, vec[0], vec[1], vec[2], vec[3]);
}

void Shader::SetUniform(const std::string& name, const glm::mat3& matrix) const
{
    auto location = glGetUniformLocation(m_id, name.c_str());
    glUniformMatrix3fv(location, 1, false, &matrix[0][0]);
}

void Shader::SetUniform(const std::string& name, const glm::mat4& matrix) const
{
    auto location = glGetUniformLocation(m_id, name.c_str());
    glUniformMatrix4fv(location, 1, false, &matrix[0][0]);
}
