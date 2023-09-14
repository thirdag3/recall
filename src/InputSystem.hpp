#pragma once

#include "Window.hpp"

class InputSystem
{
  public:
    InputSystem(const Window& window);

  private:
    const Window& m_window;
};
