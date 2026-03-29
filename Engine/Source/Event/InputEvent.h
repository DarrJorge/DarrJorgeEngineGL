#pragma once

#include <cstdlib>

namespace DarrJorge
{
enum class EventType : uint8_t
{
    WindowClose,
    WindowResize,
    MouseMove,
    MouseButton,
    MouseScroll,
    KeyPress
};

struct InputEvent
{
    EventType type;
};
}