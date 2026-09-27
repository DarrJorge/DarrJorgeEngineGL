#pragma once

#include <functional>
#include <string>
#include <cstdint>

#include "Event/Event.h"
#include "Event/InputEvent.h"

namespace DarrJorge
{
struct WindowId
{
    uint32_t value{0};
    constexpr explicit WindowId(uint32_t id) : value(id) {}

    constexpr WindowId operator++(int)
    {
        WindowId temp = *this;
        ++value;
        return temp;
    }

    constexpr auto operator<=>(const WindowId&) const = default;
};

struct WindowSettings
{
    std::string title{};
    int width{1280};
    int height{720};
    int x{100};
    int y{100};
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

    // Opaque escape hatch for backend-specific integrations (e.g. ImGui platform backends) that
    // genuinely need the native handle. Callers must know which concrete IWindow they're holding
    // before casting this back to a real type.
    [[nodiscard]] virtual void* nativeHandle() const = 0;
};
}  // namespace DarrJorge

namespace std
{
template <>
struct hash<DarrJorge::WindowId>
{
    size_t operator()(const DarrJorge::WindowId& id) const noexcept { return std::hash<uint32_t>{}(id.value); }
};
}  // namespace std