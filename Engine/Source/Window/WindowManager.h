#pragma once

#include <memory>
#include <cstdint>
#include <expected>
#include "Window/IWindow.h"

namespace DarrJorge
{
enum class WindowCreationError : uint8_t
{
    ManagerIsNotInitialized,
    CreationFailed
};

class WindowManager
{
public:
    virtual ~WindowManager() = default;

    virtual std::expected<WindowId, WindowCreationError> createWindow(const WindowSettings& settings) = 0;
    [[nodiscard]] bool allWindowsClosed() const;
    [[nodiscard]] std::shared_ptr<IWindow> getWindowById(WindowId id) const;

    virtual void update() = 0;

    [[nodiscard]] const std::unordered_map<WindowId, std::shared_ptr<IWindow>>& windows() const;

protected:
    bool m_initialized{false};
    WindowId m_windowIdCounter{1};

    std::unordered_map<WindowId, std::shared_ptr<IWindow>> m_windows;

    void cleanupClosedWindows();
};
}  // namespace DarrJorge