#pragma once

#include <memory>
#include <string_view>
#include "EngineConfig.h"

namespace DarrJorge
{
class GLFWWindowManager;
class Renderer;

class Engine final
{
public:
    Engine();
    ~Engine();

    void run();

    static constexpr std::string_view version() { return ENGINE_VERSION_STRING; }

private:
    std::unique_ptr<GLFWWindowManager> m_windowManager;
    std::unique_ptr<Renderer> m_renderer;

    bool m_initialized{false};
};
}  // namespace DarrJorge