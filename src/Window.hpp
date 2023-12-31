#pragma once

#include <string>
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ICameraContext.hpp"
#include "IInputContext.hpp"
#include "EventDispatcher.hpp"

class Window : public ICameraContext, public IInputContext
{
  public:
    Window(int width, int height, const std::string& title);
    Window(const Window& other) = delete;
    Window& operator=(Window& other) = delete;
    ~Window();
    GLFWwindow* GetWindow() const;
    void SetTitle(const std::string& title);
    bool ShouldClose() const;
    void Update() const;
    int GetWidth() const override;
    int GetHeight() const override;
    void SetLockCursor(bool shouldLock) const override;
    bool IsKeyPressed(KeyCode keyCode) const override;
    EventDispatcher& GetEventDispatcher();

  private:
    int m_width;
    int m_height;
    std::string m_title;
    GLFWwindow* m_window;
    EventDispatcher m_eventDispatcher;
};
