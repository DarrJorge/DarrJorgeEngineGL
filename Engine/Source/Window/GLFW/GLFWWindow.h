#pragma once

#include <functional>
#include <string>
#include "Window/IWindow.h"
#include "Core/Utility.h"
#include "Event/InputEvent.h"
#include "Event/Event.h"

class GLFWwindow;

namespace DarrJorge
{
class GLFWWindow final : public IWindow, public NonCopyable
{
public:
    GLFWWindow(WindowId id, const WindowSettings& settings);
    ~GLFWWindow() override;

    void setTitle(const std::string& title) override;
    void setWindowForCurrentContext() override;

    bool isValid() const override;
    bool shouldClose() const override;

    void swapBuffers() override;

    Event<const InputEvent&>& windowEvent() override;

private:
    const WindowId m_id;
    GLFWwindow* m_window{nullptr};
    Event<const InputEvent&> m_windowEvent;
};
}  // namespace DarrJorge