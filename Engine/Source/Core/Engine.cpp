#include "Engine.h"
#include "Window/GLFW/GLFWWindowManager.h"

#include "Log/Log.h"

using namespace DarrJorge;

DEFINE_LOG_CATEGORY_STATIC(LogEngine)

Engine::Engine()
{
    LOG(LogEngine, Display, "Initializing DarrJorgeEngine, version: {}", version());

    m_windowManager = std::make_unique<GLFWWindowManager>();
    const auto result = m_windowManager->createWindow(WindowSettings{});
    if (!result)
    {
        LOG(LogEngine, Error, "Failed to create main window.");
        return;
    }

    if (auto window = m_windowManager->getWindowById(result.value()))
    {
        window->setTitle(std::format("DarrJorgeEngine, version: {}", version()));
    }

    m_initialized = true;
}

Engine::~Engine() = default;

void Engine::run()
{
    if (!m_initialized) return;

    while (!m_windowManager->allWindowsClosed())
    {
        m_windowManager->update();
    }
}
