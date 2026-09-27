#pragma once

#include <memory>
#include <string_view>
#include "EngineConfig.h"
#include "Utility.h"
#include "Event/InputEvent.h"

namespace DarrJorge
{
class WindowManager;
class Renderer;
class Scene;
class EditorLayer;

class Engine final : public NonCopyable
{
public:
    Engine(std::unique_ptr<WindowManager> windowManager);
    ~Engine();

    void run();

    static constexpr std::string_view version() { return ENGINE_VERSION_STRING; }

private:
    void onWindowEvent(const InputEvent& event);

private:
    const std::unique_ptr<WindowManager> m_windowManager;
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<Scene> m_scene;
    std::unique_ptr<EditorLayer> m_editorLayer;

    bool m_initialized{false};
};
}  // namespace DarrJorge