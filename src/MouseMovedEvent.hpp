#pragma once

#include "IEvent.hpp"

class MouseMovedEvent : public IEvent
{
  public:
    MouseMovedEvent(int x, int y) : m_xPos(x), m_yPos(y)
    {
    }

    const std::string GetName() const override
    {
        return "MouseMovedEvent";
    };

    int GetX() const
    {
        return m_xPos;
    };

    int GetY() const
    {
        return m_yPos;
    };

    void SetX(int x)
    {
        m_xPos = x;
    }

    void SetY(int y)
    {
        m_yPos = y;
    };

  private:
    int m_xPos;
    int m_yPos;
};
