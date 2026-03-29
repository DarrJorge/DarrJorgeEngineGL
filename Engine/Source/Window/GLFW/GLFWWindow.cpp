#include "GLFWWindow.h"
#include <GLFW/glfw3.h>

#include "Log/Log.h"

using namespace DarrJorge;

DEFINE_LOG_CATEGORY_STATIC(LogGLFWWindow);

GLFWWindow::GLFWWindow(WindowId id, const WindowSettings& settings) : m_id(id)
{
    m_window = glfwCreateWindow(settings.width, settings.height, settings.title.c_str(), nullptr, nullptr);
    if (!m_window)
    {
        LOG(LogGLFWWindow, Error, "Failed to create GLFW window.");
        return;
    }
    glfwSetWindowPos(m_window, settings.x, settings.y);

    glfwSetWindowUserPointer(m_window, this);

    glfwSetWindowCloseCallback(m_window,
        [](GLFWwindow* window)
        {
            auto* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
            InputEvent event{};
            event.type = EventType::WindowClose;
            thisWindow->m_windowEvent.invoke(event);
        });

    glfwSetFramebufferSizeCallback(m_window,
        [](GLFWwindow* window, int width, int height)
        {
            auto* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
            InputEvent event{};
            event.type = EventType::WindowResize;
            thisWindow->m_windowEvent.invoke(event);
        });

    glfwSetKeyCallback(m_window,
        [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            auto* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
            InputEvent event{};
            event.type = EventType::KeyPress;
            thisWindow->m_windowEvent.invoke(event);
        });

    glfwSetCursorPosCallback(m_window,
        [](GLFWwindow* window, double xpos, double ypos)
        {
            auto* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
            InputEvent event{};
            event.type = EventType::MouseMove;
            thisWindow->m_windowEvent.invoke(event);
        });

    glfwSetMouseButtonCallback(m_window,
        [](GLFWwindow* window, int button, int action, int mods)
        {
            auto* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
            InputEvent event{};
            event.type = EventType::MouseButton;
            thisWindow->m_windowEvent.invoke(event);
        });

    glfwSetScrollCallback(m_window,
        [](GLFWwindow* window, double xoffset, double yoffset)
        {
            auto* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
            InputEvent event{};
            event.type = EventType::MouseScroll;
            thisWindow->m_windowEvent.invoke(event);
        });
}

GLFWWindow::~GLFWWindow()
{
    if (m_window)
    {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
}

void GLFWWindow::setTitle(const std::string& title)
{
    if (!m_window) return;
    glfwSetWindowTitle(m_window, title.c_str());
}

void GLFWWindow::setWindowForCurrentContext()
{
    if (!m_window) return;
    glfwMakeContextCurrent(m_window);
}

bool GLFWWindow::isValid() const
{
    return m_window != nullptr;
}

bool GLFWWindow::shouldClose() const
{
    if (!m_window) return true;
    return glfwWindowShouldClose(m_window);
}

void GLFWWindow::swapBuffers()
{
    if (!m_window) return;
    glfwSwapBuffers(m_window);
}