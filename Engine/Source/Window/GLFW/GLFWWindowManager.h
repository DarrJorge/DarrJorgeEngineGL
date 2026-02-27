#pragma once

#include <memory>
#include <cstdint>
#include <expected>
#include "Window/IWindow.h"
#include "Window/IWindowManager.h"

namespace DarrJorge
{
class GLFWWindowManager final : public IWindowManager
{
public:
    GLFWWindowManager();
    ~GLFWWindowManager() override;

    std::expected<WindowId, WindowCreationError> createWindow(const WindowSettings& settings) override;
    [[nodiscard]] bool allWindowsClosed() const override;
    [[nodiscard]] std::shared_ptr<IWindow> getWindowById(WindowId id) const override;

    void update() override;

    [[nodiscard]] const std::unordered_map<WindowId, std::shared_ptr<IWindow>>& windows() const override;

private:
    bool m_initialized{false};
    WindowId m_windowIdCounter{1};

    std::unordered_map<WindowId, std::shared_ptr<IWindow>> m_windows;

    void cleanupClosedWindows();
};
}  // namespace DarrJorge