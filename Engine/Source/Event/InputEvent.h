#pragma once

#include "Core/Types.h"
#include "Window/WindowId.h"
#include <variant>

namespace DarrJorge
{
enum class Key : uint16
{
    None = 0,
    Unknown,
    Esc,
    Return,
    Tab,
    Space,
    Backspace,
    Up,
    Down,
    Left,
    Right,
    Insert,
    Delete,
    Home,
    End,
    PageUp,
    PageDown,
    Print,
    Pause,
    Minus,
    Equal,
    LeftBracket,
    RightBracket,
    Semicolon,
    Quote,
    Comma,
    Period,
    Slash,
    Backslash,
    Tilde,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    F13,
    F14,
    F15,
    F16,
    F17,
    F18,
    F19,
    F20,
    F21,
    F22,
    F23,
    F24,
    F25,
    NumPad0,
    NumPad1,
    NumPad2,
    NumPad3,
    NumPad4,
    NumPad5,
    NumPad6,
    NumPad7,
    NumPad8,
    NumPad9,
    NumPadDecimal,
    NumPadDivide,
    NumPadMultiply,
    NumPadSubtract,
    NumPadAdd,
    NumPadEnter,
    NumPadEqual,
    Key0,
    Key1,
    Key2,
    Key3,
    Key4,
    Key5,
    Key6,
    Key7,
    Key8,
    Key9,
    KeyA,
    KeyB,
    KeyC,
    KeyD,
    KeyE,
    KeyF,
    KeyG,
    KeyH,
    KeyI,
    KeyJ,
    KeyK,
    KeyL,
    KeyM,
    KeyN,
    KeyO,
    KeyP,
    KeyQ,
    KeyR,
    KeyS,
    KeyT,
    KeyU,
    KeyV,
    KeyW,
    KeyX,
    KeyY,
    KeyZ,

    CapsLock,
    ScrollLock,
    NumLock,

    LeftShift,
    RightShift,
    LeftCtrl,
    RightCtrl,
    LeftAlt,
    RightAlt,
    LeftMeta,
    RightMeta,
    Menu,

    World1,
    World2,

    Count
};

enum class MouseButton : uint8
{
    Unknown = 0,
    Left,
    Right,
    Middle,
    XButton1,
    XButton2,
    Button6,
    Button7,
    Button8
};

enum class KeyAction : uint8
{
    Unknown = 0,
    Pressed,
    Released,
    Repeat
};

enum class EventType : uint8
{
    None = 0,
    WindowClose,
    WindowResize,
    MouseMove,
    MouseButton,
    MouseScroll,
    Key
};

struct MouseMoveEventData
{
    double x{};
    double y{};
};

struct MouseScrollEventData
{
    double xOffset{};
    double yOffset{};
};

struct WindowResizeEventData
{
    int32 width{};
    int32 height{};
};

struct WindowCloseEventData
{
};

struct KeyEventData
{
    Key key{Key::None};
    KeyAction action{KeyAction::Unknown};
    int32 scanCode{};
};

struct MouseButtonEventData
{
    MouseButton button{MouseButton::Unknown};
    KeyAction action{KeyAction::Unknown};
};

using EventData = std::variant<std::monostate, MouseMoveEventData, MouseScrollEventData, WindowResizeEventData, WindowCloseEventData, KeyEventData,
    MouseButtonEventData>;

struct InputEvent
{
    WindowId windowId{};
    EventData data;

    [[nodiscard]] constexpr EventType type() const noexcept { return static_cast<EventType>(data.index()); }
};
}  // namespace DarrJorge