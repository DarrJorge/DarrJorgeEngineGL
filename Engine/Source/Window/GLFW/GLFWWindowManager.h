#pragma once

#include <memory>
#include <cstdint>
#include <expected>
#include "GLFWWindow.h"

namespace DarrJorge
{
class GLFWWindow;

enum class WindowCreationError : uint8_t
{
    ManagerIsNotInitialized,
    CreationFailed
};

class GLFWWindowManager final
{
public:
    GLFWWindowManager();
    ~GLFWWindowManager();

    std::expected<WindowId, WindowCreationError> createWindow(const WindowSettings& settings);
    [[nodiscard]] bool allWindowsClosed() const;
    [[nodiscard]] std::shared_ptr<GLFWWindow> getWindowById(WindowId id) const;

    void update();

    [[nodiscard]] const std::unordered_map<WindowId, std::shared_ptr<GLFWWindow>>& windows() const;

private:
    bool m_initialized{false};
    WindowId m_windowIdCounter{1};

    std::unordered_map<WindowId, std::shared_ptr<GLFWWindow>> m_windows;

    void cleanupClosedWindows();
};
}  // namespace DarrJorge