#pragma once

#include "Core/Types.h"
#include "Window/WindowId.h"
#include <variant>
#include <string_view>

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
    None = 0,
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
    None = 0,
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
    KeyAction action{KeyAction::None};
    int32 scanCode{};
};

struct MouseButtonEventData
{
    MouseButton button{MouseButton::None};
    KeyAction action{KeyAction::None};
};

using EventData = std::variant<std::monostate,  //
    WindowCloseEventData,                       //
    WindowResizeEventData,                      //
    MouseMoveEventData,                         //
    MouseButtonEventData,                       //
    MouseScrollEventData,                       //
    KeyEventData>;

struct InputEvent
{
    WindowId windowId{};
    EventData data;

    [[nodiscard]] constexpr EventType type() const noexcept { return static_cast<EventType>(data.index()); }
};

[[nodiscard]] constexpr std::string_view toString(Key key) noexcept
{
    switch (key)
    {
        case Key::None: return "None";
        case Key::Unknown: return "Unknown";
        case Key::Esc: return "Esc";
        case Key::Return: return "Return";
        case Key::Tab: return "Tab";
        case Key::Space: return "Space";
        case Key::Backspace: return "Backspace";
        case Key::Up: return "Up";
        case Key::Down: return "Down";
        case Key::Left: return "Left";
        case Key::Right: return "Right";
        case Key::Insert: return "Insert";
        case Key::Delete: return "Delete";
        case Key::Home: return "Home";
        case Key::End: return "End";
        case Key::PageUp: return "PageUp";
        case Key::PageDown: return "PageDown";
        case Key::Print: return "Print";
        case Key::Pause: return "Pause";
        case Key::Minus: return "Minus";
        case Key::Equal: return "Equal";
        case Key::LeftBracket: return "LeftBracket";
        case Key::RightBracket: return "RightBracket";
        case Key::Semicolon: return "Semicolon";
        case Key::Quote: return "Quote";
        case Key::Comma: return "Comma";
        case Key::Period: return "Period";
        case Key::Slash: return "Slash";
        case Key::Backslash: return "Backslash";
        case Key::Tilde: return "Tilde";
        case Key::F1: return "F1";
        case Key::F2: return "F2";
        case Key::F3: return "F3";
        case Key::F4: return "F4";
        case Key::F5: return "F5";
        case Key::F6: return "F6";
        case Key::F7: return "F7";
        case Key::F8: return "F8";
        case Key::F9: return "F9";
        case Key::F10: return "F10";
        case Key::F11: return "F11";
        case Key::F12: return "F12";
        case Key::F13: return "F13";
        case Key::F14: return "F14";
        case Key::F15: return "F15";
        case Key::F16: return "F16";
        case Key::F17: return "F17";
        case Key::F18: return "F18";
        case Key::F19: return "F19";
        case Key::F20: return "F20";
        case Key::F21: return "F21";
        case Key::F22: return "F22";
        case Key::F23: return "F23";
        case Key::F24: return "F24";
        case Key::F25: return "F25";
        case Key::NumPad0: return "NumPad0";
        case Key::NumPad1: return "NumPad1";
        case Key::NumPad2: return "NumPad2";
        case Key::NumPad3: return "NumPad3";
        case Key::NumPad4: return "NumPad4";
        case Key::NumPad5: return "NumPad5";
        case Key::NumPad6: return "NumPad6";
        case Key::NumPad7: return "NumPad7";
        case Key::NumPad8: return "NumPad8";
        case Key::NumPad9: return "NumPad9";
        case Key::NumPadDecimal: return "NumPadDecimal";
        case Key::NumPadDivide: return "NumPadDivide";
        case Key::NumPadMultiply: return "NumPadMultiply";
        case Key::NumPadSubtract: return "NumPadSubtract";
        case Key::NumPadAdd: return "NumPadAdd";
        case Key::NumPadEnter: return "NumPadEnter";
        case Key::NumPadEqual: return "NumPadEqual";
        case Key::Key0: return "Key0";
        case Key::Key1: return "Key1";
        case Key::Key2: return "Key2";
        case Key::Key3: return "Key3";
        case Key::Key4: return "Key4";
        case Key::Key5: return "Key5";
        case Key::Key6: return "Key6";
        case Key::Key7: return "Key7";
        case Key::Key8: return "Key8";
        case Key::Key9: return "Key9";
        case Key::KeyA: return "KeyA";
        case Key::KeyB: return "KeyB";
        case Key::KeyC: return "KeyC";
        case Key::KeyD: return "KeyD";
        case Key::KeyE: return "KeyE";
        case Key::KeyF: return "KeyF";
        case Key::KeyG: return "KeyG";
        case Key::KeyH: return "KeyH";
        case Key::KeyI: return "KeyI";
        case Key::KeyJ: return "KeyJ";
        case Key::KeyK: return "KeyK";
        case Key::KeyL: return "KeyL";
        case Key::KeyM: return "KeyM";
        case Key::KeyN: return "KeyN";
        case Key::KeyO: return "KeyO";
        case Key::KeyP: return "KeyP";
        case Key::KeyQ: return "KeyQ";
        case Key::KeyR: return "KeyR";
        case Key::KeyS: return "KeyS";
        case Key::KeyT: return "KeyT";
        case Key::KeyU: return "KeyU";
        case Key::KeyV: return "KeyV";
        case Key::KeyW: return "KeyW";
        case Key::KeyX: return "KeyX";
        case Key::KeyY: return "KeyY";
        case Key::KeyZ: return "KeyZ";
        case Key::CapsLock: return "CapsLock";
        case Key::ScrollLock: return "ScrollLock";
        case Key::NumLock: return "NumLock";
        case Key::LeftShift: return "LeftShift";
        case Key::RightShift: return "RightShift";
        case Key::LeftCtrl: return "LeftCtrl";
        case Key::RightCtrl: return "RightCtrl";
        case Key::LeftAlt: return "LeftAlt";
        case Key::RightAlt: return "RightAlt";
        case Key::LeftMeta: return "LeftMeta";
        case Key::RightMeta: return "RightMeta";
        case Key::Menu: return "Menu";
        case Key::World1: return "World1";
        case Key::World2: return "World2";
        case Key::Count: break;
    }
    return "Unknown";
}

[[nodiscard]] constexpr std::string_view toString(KeyAction action) noexcept
{
    switch (action)
    {
        case KeyAction::Released: return "Released";
        case KeyAction::Pressed: return "Pressed";
        case KeyAction::Repeat: return "Repeat";
        case KeyAction::None: return "Unknown";
    }
    return "Unknown";
}

[[nodiscard]] constexpr std::string_view toString(MouseButton button) noexcept
{
    switch (button)
    {
        case MouseButton::None: return "None";
        case MouseButton::Left: return "Left";
        case MouseButton::Middle: return "Middle";
        case MouseButton::Right: return "Right";
        case MouseButton::XButton1: return "XButton1";
        case MouseButton::XButton2: return "XButton2";
        case MouseButton::Button6: return "Button6";
        case MouseButton::Button7: return "Button7";
        case MouseButton::Button8: return "Button8";
    }
    return "Unknown";
}

[[nodiscard]] constexpr std::string_view toString(EventType type) noexcept
{
    switch (type)
    {
        case EventType::None: return "None";
        case EventType::WindowClose: return "WindowClose";
        case EventType::WindowResize: return "WindowResize";
        case EventType::Key: return "Key";
        case EventType::MouseButton: return "MouseButton";
        case EventType::MouseMove: return "MouseMove";
        case EventType::MouseScroll: return "MouseScroll";
    }
    return "Unknown";
}
}  // namespace DarrJorge