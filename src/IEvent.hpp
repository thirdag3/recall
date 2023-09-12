#pragma once

#include <string>

class IEvent
{
  public:
    virtual const std::string GetName() const = 0;
};
