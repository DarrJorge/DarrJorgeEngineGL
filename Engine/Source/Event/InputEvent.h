#pragma once

#include <cstdlib>
#include <variant>

namespace DarrJorge
{
enum class KeyCode : uint8_t { Unknown = 0, W, A, S, D, Count };
enum class KeyAction : uint8_t { Pressed, Released };
enum class MouseButton : uint8_t { Unknown = 0, Left, Right, Middle };

enum class EventType : uint8_t
{
    WindowClose,
    WindowResize,
    MouseMove,
    MouseButton,
    MouseScroll,
    KeyPress
};

struct MouseMoveEventData
{
    double x;
    double y;
};

struct MouseScrollEventData
{
    double xOffset;
    double yOffset;
};

struct WindowResizeEventData
{
    int width;
    int height;
};

struct WindowCloseEventData
{
    unsigned int id;
};

struct KeyEventData
{
    KeyCode key;
    KeyAction action;
};

struct MouseButtonEventData
{
    MouseButton button;
    KeyAction action;
};

using EventData = std::variant<std::monostate, MouseMoveEventData, MouseScrollEventData, WindowResizeEventData, WindowCloseEventData, KeyEventData,
    MouseButtonEventData>;

struct InputEvent
{
    EventType type;
    EventData data;
};
}  // namespace DarrJorge