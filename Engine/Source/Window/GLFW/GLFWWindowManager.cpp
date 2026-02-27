#include "GLFWWindowManager.h"
#include <GLFW/glfw3.h>
#include "GLFWWindow.h"

#include "Log/Log.h"

using namespace DarrJorge;

DEFINE_LOG_CATEGORY_STATIC(LogGLFWWindowManager);

GLFWWindowManager::GLFWWindowManager()
{
    glfwSetErrorCallback([](int errorCode, const char* description)
                         { LOG(LogGLFWWindowManager, Error, "GLFW error, code: {}, description: {}", errorCode, description); });

    if (!glfwInit())
    {
        LOG(LogGLFWWindowManager, Error, "Failed to initialize GLFW");
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_initialized = true;

    LOG(LogGLFWWindowManager, Display, "GLFW initialized successfully.");
}

GLFWWindowManager::~GLFWWindowManager()
{
    m_windows.clear();

    if (m_initialized)
    {
        glfwSetErrorCallback(nullptr);
        glfwTerminate();
    }

    m_initialized = false;

    LOG(LogGLFWWindowManager, Display, "GLFW shutdown complete!");
}

std::expected<WindowId, WindowCreationError> GLFWWindowManager::createWindow(const WindowSettings& settings)
{
    if (!m_initialized)
    {
        LOG(LogGLFWWindowManager, Error, "Cannot create window. GLFW is not initialized.");
        return std::unexpected(WindowCreationError::ManagerIsNotInitialized);
    }

    auto window = std::make_shared<GLFWWindow>(settings);
    if (!window->isValid())
    {
        LOG(LogGLFWWindowManager, Error, "Failed to create window.");
        return std::unexpected(WindowCreationError::CreationFailed);
    }

    window->setWindowForCurrentContext();

    const WindowId id = m_windowIdCounter++;
    m_windows[id] = window;

    LOG(LogGLFWWindowManager, Display, "Adding window with id {}", id.value);

    return id;
}

bool GLFWWindowManager::allWindowsClosed() const
{
    return m_windows.empty();
}

std::shared_ptr<IWindow> GLFWWindowManager::getWindowById(WindowId id) const
{
    const auto it = m_windows.find(id);
    return it != m_windows.end() ? it->second : nullptr;
}

void GLFWWindowManager::update()
{
    if (!m_initialized) return;

    glfwPollEvents();
    cleanupClosedWindows();

    for (auto& window : m_windows)
    {
        window.second->swapBuffers();
    }
}

const std::unordered_map<WindowId, std::shared_ptr<IWindow>>& GLFWWindowManager::windows() const
{
    return m_windows;
}

void GLFWWindowManager::cleanupClosedWindows()
{
    auto it = m_windows.begin();
    while (it != m_windows.end())
    {
        if (it->second->shouldClose())
        {
            LOG(LogGLFWWindowManager, Display, "Removing window with id {}", it->first.value);
            it = m_windows.erase(it);
            continue;
        }
        it++;
    }
}