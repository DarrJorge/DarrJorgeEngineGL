#include "GLFWWindow.h"
#include "GLFWKeyMapper.h"
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
            if (!thisWindow) return;

            InputEvent event{};
            event.windowId = thisWindow->m_id;
            event.data = WindowCloseEventData{};
            thisWindow->m_windowEvent.invoke(event);
        });

    glfwSetFramebufferSizeCallback(m_window,
        [](GLFWwindow* window, int width, int height)
        {
            auto* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
            if (!thisWindow) return;

            InputEvent event{};
            event.windowId = thisWindow->m_id;
            event.data = WindowResizeEventData{width, height};
            thisWindow->m_windowEvent.invoke(event);
        });

    glfwSetKeyCallback(m_window,
        [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (action != GLFW_PRESS && action != GLFW_RELEASE) return;

            auto* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
            if (!thisWindow) return;

            InputEvent event{};
            event.windowId = thisWindow->m_id;
            event.data = KeyEventData{
                .key = KeyMapper::toKey(key),
                .action = KeyMapper::toAction(action),
                .scanCode = scancode};
            thisWindow->m_windowEvent.invoke(event);
        });

    glfwSetCursorPosCallback(m_window,
        [](GLFWwindow* window, double xPos, double yPos)
        {
            auto* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
            if (!thisWindow) return;

            InputEvent event{};
            event.windowId = thisWindow->m_id;
            event.data = MouseMoveEventData{xPos, yPos};
            thisWindow->m_windowEvent.invoke(event);
        });

    glfwSetMouseButtonCallback(m_window,
        [](GLFWwindow* window, int button, int action, int mods)
        {
            if (action != GLFW_PRESS && action != GLFW_RELEASE) return;

            auto* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
            if (!thisWindow) return;

            InputEvent event{};
            event.windowId = thisWindow->m_id;
            event.data = MouseButtonEventData{
                .button = KeyMapper::toMouseButton(button),
                .action = KeyMapper::toAction(action)};
            thisWindow->m_windowEvent.invoke(event);
        });

    glfwSetScrollCallback(m_window,
        [](GLFWwindow* window, double xOffset, double yOffset)
        {
            auto* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
            if (!thisWindow) return;

            InputEvent event{};
            event.windowId = thisWindow->m_id;
            event.data = MouseScrollEventData{xOffset, yOffset};
            thisWindow->m_windowEvent.invoke(event);
        });
}

GLFWWindow::~GLFWWindow()
{
    if (m_window)
    {
        glfwSetWindowUserPointer(m_window, nullptr);
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

Event<const InputEvent&>& GLFWWindow::windowEvent()
{
    return m_windowEvent;
}

void* GLFWWindow::nativeHandle() const
{
    return m_window;
}

void GLFWWindow::setCursorMode(CursorMode mode)
{
    if (!m_window) return;
    glfwSetInputMode(m_window, GLFW_CURSOR, mode == CursorMode::Disabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}
