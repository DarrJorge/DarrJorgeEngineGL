#pragma once

#include <functional>
#include <string>
#include <cstdint>

#include "Event/Event.h"
#include "Event/InputEvent.h"
#include "Core/Types.h"

namespace DarrJorge
{
struct WindowSettings
{
    std::string title{};
    int width{1280};
    int height{720};
    int x{100};
    int y{100};
};

enum class CursorMode : uint8_t
{
    Normal,
    Disabled
};

class IWindow
{
public:
    virtual ~IWindow() = default;

    virtual void setTitle(const std::string& title) = 0;
    virtual void setWindowForCurrentContext() = 0;
    virtual void swapBuffers() = 0;

    virtual bool isValid() const = 0;
    virtual bool shouldClose() const = 0;

    virtual Event<const InputEvent&>& windowEvent() = 0;

    virtual void setCursorMode(CursorMode mode) = 0;

    // Opaque escape hatch for backend-specific integrations (e.g. ImGui platform backends) that
    // genuinely need the native handle. Callers must know which concrete IWindow they're holding
    // before casting this back to a real type.
    [[nodiscard]] virtual void* nativeHandle() const = 0;
};
}  // namespace DarrJorge