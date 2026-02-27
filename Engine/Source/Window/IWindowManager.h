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

class IWindowManager
{
public:
    virtual ~IWindowManager() = default;

    virtual std::expected<WindowId, WindowCreationError> createWindow(const WindowSettings& settings) = 0;
    [[nodiscard]] virtual bool allWindowsClosed() const = 0;
    [[nodiscard]] virtual std::shared_ptr<IWindow> getWindowById(WindowId id) const = 0;

    virtual void update() = 0;

    [[nodiscard]] virtual const std::unordered_map<WindowId, std::shared_ptr<IWindow>>& windows() const = 0;
};
}  // namespace DarrJorge