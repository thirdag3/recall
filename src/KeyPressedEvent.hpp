#pragma once

#include "IEvent.hpp"

#include "KeyCode.hpp"

class KeyPressedEvent : public IEvent
{
  public:
    KeyPressedEvent(KeyCode keyCode) : m_keyCode(keyCode)
    {
    }

    const std::string GetName() const override
    {
        return "KeyPressedEvent";
    };

    KeyCode GetKeycode() const
    {
        return m_keyCode;
    };

    void SetKeycode(KeyCode keyCode)
    {
        m_keyCode = keyCode;
    }

  private:
    KeyCode m_keyCode;
};
