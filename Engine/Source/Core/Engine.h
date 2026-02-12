#pragma once

#include <memory>
#include <string_view>

namespace DarrJorge
{
class GLFWWindowManager;

class Engine final
{
public:
    Engine();
    ~Engine();

    void run();

    static constexpr std::string_view version() { return "1.0.0"; }

private:
    std::unique_ptr<GLFWWindowManager> m_windowManager;
    bool m_initialized{false};
};
}  // namespace DarrJorge