#include "Engine.h"
#include "Window/WindowManager.h"
#include "Render/Renderer/Renderer.h"
#include <chrono>

#include "Log/Log.h"

using namespace DarrJorge;

DEFINE_LOG_CATEGORY_STATIC(LogEngine)

Engine::Engine(std::unique_ptr<WindowManager> windowManager) : m_windowManager(std::move(windowManager))
{
    LOG(LogEngine, Display, "Initializing {}, version: {}", ENGINE_TITLE_STRING, version());

    const auto result = m_windowManager->createWindow(WindowSettings{});
    if (!result)
    {
        LOG(LogEngine, Error, "Failed to create main window.");
        return;
    }

    if (auto window = m_windowManager->getWindowById(result.value()))
    {
        window->setTitle(std::format("{}, version: {}", ENGINE_TITLE_STRING, version()));
    }

    m_renderer = std::make_unique<Renderer>();

    m_initialized = true;
}

Engine::~Engine() = default;

void Engine::run()
{
    if (!m_initialized) return;

    auto m_lastTimePoint = std::chrono::high_resolution_clock::now();

    while (!m_windowManager->allWindowsClosed())
    {
        const auto now = std::chrono::high_resolution_clock::now();
        const auto deltaTime = std::chrono::duration<float>(now - m_lastTimePoint).count();
        m_lastTimePoint = now;

        m_renderer->tick(deltaTime);
        m_windowManager->update();
    }
}
