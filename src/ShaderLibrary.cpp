#include "ShaderLibrary.hpp"

void ShaderLibrary::Initialize()
{
    if (!m_standardPhong) {
        m_standardPhong = std::make_unique<Shader>("Assets/Shaders/Phong.vert", "Assets/Shaders/Phong.frag");
    }
}

std::shared_ptr<Shader> ShaderLibrary::GetStandardPhong()
{
    return ShaderLibrary::m_standardPhong;
}

void ShaderLibrary::SetStandardPhong(std::shared_ptr<Shader> shader)
{
    m_standardPhong = shader;
}
