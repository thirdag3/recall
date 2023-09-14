#pragma once

#include "IEvent.hpp"

class MouseMovedEvent : public IEvent
{
  public:
    MouseMovedEvent(float x, float y) : m_xPos(x), m_yPos(y)
    {
    }

    const std::string GetName() const override
    {
        return "MouseMovedEvent";
    };

    float GetX() const
    {
        return m_xPos;
    };

    float GetY() const
    {
        return m_yPos;
    };

    void SetX(float x)
    {
        m_xPos = x;
    }

    void SetY(float y)
    {
        m_yPos = y;
    };

  private:
    float m_xPos;
    float m_yPos;
};
