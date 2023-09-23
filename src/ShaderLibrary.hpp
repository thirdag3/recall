#pragma once

#include <memory>

#include "Shader.hpp"

class ShaderLibrary
{
  public:
    static void Initialize();
    static std::shared_ptr<Shader> GetStandardPhong();
    static void SetStandardPhong(std::shared_ptr<Shader> shader);

private:
    inline static std::shared_ptr<Shader> m_standardPhong = nullptr;
};
