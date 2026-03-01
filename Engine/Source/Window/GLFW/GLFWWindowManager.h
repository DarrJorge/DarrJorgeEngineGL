#pragma once

#include <memory>
#include <cstdint>
#include <expected>
#include "Window/IWindow.h"
#include "Window/WindowManager.h"
#include "Core/Utility.h"

namespace DarrJorge
{
class GLFWWindowManager final : public WindowManager, public NonCopyable
{
public:
    GLFWWindowManager();
    ~GLFWWindowManager() override;

    std::expected<WindowId, WindowCreationError> createWindow(const WindowSettings& settings) override;

    void update() override;
};
}  // namespace DarrJorge