#pragma once

#include "KeyCode.hpp"

class IInputContext
{
  public:
    virtual ~IInputContext() = default;
    virtual bool IsKeyPressed(KeyCode keyCode) const = 0;
};
