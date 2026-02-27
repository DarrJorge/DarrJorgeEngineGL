#pragma once

#include <memory>
#include <string_view>
#include "EngineConfig.h"
#include "Utility.h"

namespace DarrJorge
{
class IWindowManager;
class Renderer;

class Engine final : public NonCopyable
{
public:
    Engine(std::unique_ptr<IWindowManager> windowManager);
    ~Engine();

    void run();

    static constexpr std::string_view version() { return ENGINE_VERSION_STRING; }

private:
    const std::unique_ptr<IWindowManager> m_windowManager;
    std::unique_ptr<Renderer> m_renderer;

    bool m_initialized{false};
};
}  // namespace DarrJorge