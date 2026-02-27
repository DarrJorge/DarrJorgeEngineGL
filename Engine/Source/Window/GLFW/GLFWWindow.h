#pragma once

#include <functional>
#include <string>
#include "Window/IWindow.h"

class GLFWwindow;

namespace DarrJorge
{
class GLFWWindow final : public IWindow
{
public:
    GLFWWindow(const WindowSettings& settings);
    ~GLFWWindow() override;

    void setTitle(const std::string& title) override;
    void setWindowForCurrentContext() override;

    bool isValid() const override;
    bool shouldClose() const override;

    void swapBuffers() override;

private:
    GLFWwindow* m_window{nullptr};
};
}  // namespace DarrJorge