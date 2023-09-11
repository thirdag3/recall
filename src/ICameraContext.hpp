#pragma once

class ICameraContext
{
  public:
    virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;
    virtual void SetLockCursor(bool shouldLock) const = 0;
};
