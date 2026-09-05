#include "Engine.h"
#include "Window/WindowManager.h"
#include "Render/Renderer/Renderer.h"
#include "Scene/Scene.h"
#include "Scene/SceneFactory.h"
#include "Log/Log.h"

#include <chrono>

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
        window->windowEvent().add(this, &Engine::onWindowEvent);
    }

    m_renderer = std::make_unique<Renderer>();
    m_scene = std::move(SceneFactory::createDemoScene());

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

        m_scene->update(deltaTime);

        m_renderer->render(*m_scene);

        m_windowManager->update();
    }
}
void Engine::onWindowEvent(const InputEvent& event)
{
    if (auto* data = std::get_if<MouseScrollEventData>(&event.data))
    {
        LOG(LogEngine, Display, "Mouse scroll");
    }
    else if (auto* data = std::get_if<MouseMoveEventData>(&event.data))
    {
        LOG(LogEngine, Display, "Mouse move");
    }
    else if (auto* data = std::get_if<WindowResizeEventData>(&event.data))
    {
        LOG(LogEngine, Display, "Window Resize");

        m_renderer->onResize(data->width, data->height);
        m_scene->onResize(data->width, data->height);

    }
    else if (auto* data = std::get_if<WindowCloseEventData>(&event.data))
    {
        LOG(LogEngine, Display, "Window close");
    }
}
