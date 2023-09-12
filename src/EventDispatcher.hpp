#pragma once

#include <vector>
#include <functional>

#include "IEvent.hpp"

class EventDispatcher
{
  public:
    void Dispatch(const IEvent& ev);
    void AddListener(std::function<void(const IEvent&)> listener);

  private:
    std::vector<std::function<void(const IEvent&)>> m_listeners;
};
