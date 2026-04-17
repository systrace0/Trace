#include "Window.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <cstdio>
#include <stdexcept>

#include "Core.h"

namespace engine
{
Window::Window(int width, int height, const char *title) : m_width(width), m_height(height)
{
    // Each failure path cleans up what it already initialized
    // This is the alternative to a giant nested if-chain
    if (!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Debug context in debug builds - gives better GL error messages
#ifndef NDEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!m_window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD");
    }

    std::printf("[Window] Created %dx%d | OpenGL %s\n", width, height,
                (const char *)glGetString(GL_VERSION));
}

Window::~Window()
{
    // Guard against destroying a moved-from object
    if (m_window)
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }
}

Window::Window(Window &&other) noexcept
    : m_window(other.m_window), m_width(other.m_width), m_height(other.m_height)
{
    // Null out the source so its destructor doesn't double-free
    other.m_window = nullptr;
}

Window &Window::operator=(Window &&other) noexcept
{
    if (this != &other)
    {
        // Release what we currently own
        if (m_window)
        {
            glfwDestroyWindow(m_window);
            glfwTerminate();
        }

        m_window       = other.m_window;
        m_width        = other.m_width;
        m_height       = other.m_height;
        other.m_window = nullptr;
    }
    return *this;
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(m_window);
}

void Window::swapBuffers() const
{
    glfwSwapBuffers(m_window);
}

void Window::pollEvents() const
{
    glfwPollEvents();
}
} // namespace engine