#pragma once

#include "Core/Utility.h"
#include "Window/IWindow.h"
#include <string>
#include <functional>
#include <Windows.h>

namespace DarrJorge
{
class WinAPIWindow final : public IWindow, public NonCopyable
{
public:
    WinAPIWindow(const WindowSettings& settings, HINSTANCE hInstance, const std::string& className);
    ~WinAPIWindow() override;

    void setTitle(const std::string& title) override;
    void setWindowForCurrentContext() override;

    bool isValid() const override;
    bool shouldClose() const override;
    void swapBuffers() override;

private:
    HWND m_window{nullptr};
};
}  // namespace DarrJorge