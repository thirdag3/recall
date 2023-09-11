#pragma once

#include <string>
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
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
    int GetWidth() const;
    int GetHeight() const;

  private:
    int m_width;
    int m_height;
    std::string m_title;
    GLFWwindow* m_window;
};
