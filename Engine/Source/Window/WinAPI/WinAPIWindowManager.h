#pragma once

#include <unordered_map>
#include <Windows.h>
#include "Core/Utility.h"
#include "Window/WindowManager.h"
#include "Window/IWindow.h"

namespace DarrJorge
{
class WinAPIWindowManager final : public WindowManager, public NonCopyable
{
public:
    WinAPIWindowManager();
    ~WinAPIWindowManager() override;

    void update() override;
    std::expected<WindowId, WindowCreationError> createWindow(const WindowSettings& settings) override;

private:
    HINSTANCE m_hInstance{nullptr};
};
}  // namespace DarrJorge