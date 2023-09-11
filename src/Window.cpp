#include <Window.hpp>

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void APIENTRY DebugOutputCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    std::cout << "[OpenGL]: " << message << std::endl;
}

Window::Window(int width, int height, const std::string& title)
: m_width(width),
  m_height(height),
  m_title(title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Debug Output
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (m_window == nullptr) {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        return;
    }

    glViewport(0, 0, width, height);

    glfwSetWindowUserPointer(m_window, this);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(DebugOutputCallback, nullptr);

    glfwSetKeyCallback(m_window,
        [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            const auto& self =
                *static_cast<Window*>(glfwGetWindowUserPointer(window));

            switch (action) {
            case GLFW_PRESS:
                return;

            case GLFW_REPEAT:
                return;
            }
        });

    glfwSetFramebufferSizeCallback(
        m_window, [](GLFWwindow* window, int width, int height) {
            const auto& self =
                *static_cast<Window*>(glfwGetWindowUserPointer(window));

            glViewport(0, 0, width, height);
        });
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

GLFWwindow* Window::GetWindow() const
{
    return m_window;
}

void Window::SetTitle(const std::string& title)
{
    m_title = title;
    glfwSetWindowTitle(m_window, title.c_str());
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(m_window);
}

void Window::Update() const
{
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}

int Window::GetWidth() const
{
    return m_width;
}

int Window::GetHeight() const
{
    return m_height;
}
