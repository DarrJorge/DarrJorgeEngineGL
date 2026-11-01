#include "GLFWKeyMapper.h"
#include <GLFW/glfw3.h>

namespace DarrJorge::KeyMapper
{
Key toKey(int glfwKey) noexcept
{
    switch (glfwKey)
    {
        case GLFW_KEY_ESCAPE: return Key::Esc;
        case GLFW_KEY_ENTER: return Key::Return;
        case GLFW_KEY_TAB: return Key::Tab;
        case GLFW_KEY_BACKSPACE: return Key::Backspace;
        case GLFW_KEY_SPACE: return Key::Space;
        case GLFW_KEY_INSERT: return Key::Insert;
        case GLFW_KEY_DELETE: return Key::Delete;
        case GLFW_KEY_UP: return Key::Up;
        case GLFW_KEY_DOWN: return Key::Down;
        case GLFW_KEY_LEFT: return Key::Left;
        case GLFW_KEY_RIGHT: return Key::Right;
        case GLFW_KEY_PAGE_UP: return Key::PageUp;
        case GLFW_KEY_PAGE_DOWN: return Key::PageDown;
        case GLFW_KEY_HOME: return Key::Home;
        case GLFW_KEY_END: return Key::End;
        case GLFW_KEY_PRINT_SCREEN: return Key::Print;
        case GLFW_KEY_PAUSE: return Key::Pause;
        case GLFW_KEY_EQUAL: return Key::Equal;
        case GLFW_KEY_MINUS: return Key::Minus;
        case GLFW_KEY_LEFT_BRACKET: return Key::LeftBracket;
        case GLFW_KEY_RIGHT_BRACKET: return Key::RightBracket;
        case GLFW_KEY_SEMICOLON: return Key::Semicolon;
        case GLFW_KEY_APOSTROPHE: return Key::Quote;
        case GLFW_KEY_GRAVE_ACCENT: return Key::Tilde;
        case GLFW_KEY_BACKSLASH: return Key::Backslash;
        case GLFW_KEY_COMMA: return Key::Comma;
        case GLFW_KEY_PERIOD: return Key::Period;
        case GLFW_KEY_SLASH: return Key::Slash;

        case GLFW_KEY_F1: return Key::F1;
        case GLFW_KEY_F2: return Key::F2;
        case GLFW_KEY_F3: return Key::F3;
        case GLFW_KEY_F4: return Key::F4;
        case GLFW_KEY_F5: return Key::F5;
        case GLFW_KEY_F6: return Key::F6;
        case GLFW_KEY_F7: return Key::F7;
        case GLFW_KEY_F8: return Key::F8;
        case GLFW_KEY_F9: return Key::F9;
        case GLFW_KEY_F10: return Key::F10;
        case GLFW_KEY_F11: return Key::F11;
        case GLFW_KEY_F12: return Key::F12;
        case GLFW_KEY_F13: return Key::F13;
        case GLFW_KEY_F14: return Key::F14;
        case GLFW_KEY_F15: return Key::F15;
        case GLFW_KEY_F16: return Key::F16;
        case GLFW_KEY_F17: return Key::F17;
        case GLFW_KEY_F18: return Key::F18;
        case GLFW_KEY_F19: return Key::F19;
        case GLFW_KEY_F20: return Key::F20;
        case GLFW_KEY_F21: return Key::F21;
        case GLFW_KEY_F22: return Key::F22;
        case GLFW_KEY_F23: return Key::F23;
        case GLFW_KEY_F24: return Key::F24;
        case GLFW_KEY_F25: return Key::F25;

        case GLFW_KEY_KP_0: return Key::NumPad0;
        case GLFW_KEY_KP_1: return Key::NumPad1;
        case GLFW_KEY_KP_2: return Key::NumPad2;
        case GLFW_KEY_KP_3: return Key::NumPad3;
        case GLFW_KEY_KP_4: return Key::NumPad4;
        case GLFW_KEY_KP_5: return Key::NumPad5;
        case GLFW_KEY_KP_6: return Key::NumPad6;
        case GLFW_KEY_KP_7: return Key::NumPad7;
        case GLFW_KEY_KP_8: return Key::NumPad8;
        case GLFW_KEY_KP_9: return Key::NumPad9;
        case GLFW_KEY_KP_DECIMAL: return Key::NumPadDecimal;
        case GLFW_KEY_KP_DIVIDE: return Key::NumPadDivide;
        case GLFW_KEY_KP_MULTIPLY: return Key::NumPadMultiply;
        case GLFW_KEY_KP_SUBTRACT: return Key::NumPadSubtract;
        case GLFW_KEY_KP_ADD: return Key::NumPadAdd;
        case GLFW_KEY_KP_ENTER: return Key::NumPadEnter;
        case GLFW_KEY_KP_EQUAL: return Key::NumPadEqual;

        case GLFW_KEY_0: return Key::Key0;
        case GLFW_KEY_1: return Key::Key1;
        case GLFW_KEY_2: return Key::Key2;
        case GLFW_KEY_3: return Key::Key3;
        case GLFW_KEY_4: return Key::Key4;
        case GLFW_KEY_5: return Key::Key5;
        case GLFW_KEY_6: return Key::Key6;
        case GLFW_KEY_7: return Key::Key7;
        case GLFW_KEY_8: return Key::Key8;
        case GLFW_KEY_9: return Key::Key9;

        case GLFW_KEY_A: return Key::KeyA;
        case GLFW_KEY_B: return Key::KeyB;
        case GLFW_KEY_C: return Key::KeyC;
        case GLFW_KEY_D: return Key::KeyD;
        case GLFW_KEY_E: return Key::KeyE;
        case GLFW_KEY_F: return Key::KeyF;
        case GLFW_KEY_G: return Key::KeyG;
        case GLFW_KEY_H: return Key::KeyH;
        case GLFW_KEY_I: return Key::KeyI;
        case GLFW_KEY_J: return Key::KeyJ;
        case GLFW_KEY_K: return Key::KeyK;
        case GLFW_KEY_L: return Key::KeyL;
        case GLFW_KEY_M: return Key::KeyM;
        case GLFW_KEY_N: return Key::KeyN;
        case GLFW_KEY_O: return Key::KeyO;
        case GLFW_KEY_P: return Key::KeyP;
        case GLFW_KEY_Q: return Key::KeyQ;
        case GLFW_KEY_R: return Key::KeyR;
        case GLFW_KEY_S: return Key::KeyS;
        case GLFW_KEY_T: return Key::KeyT;
        case GLFW_KEY_U: return Key::KeyU;
        case GLFW_KEY_V: return Key::KeyV;
        case GLFW_KEY_W: return Key::KeyW;
        case GLFW_KEY_X: return Key::KeyX;
        case GLFW_KEY_Y: return Key::KeyY;
        case GLFW_KEY_Z: return Key::KeyZ;

        case GLFW_KEY_CAPS_LOCK: return Key::CapsLock;
        case GLFW_KEY_SCROLL_LOCK: return Key::ScrollLock;
        case GLFW_KEY_NUM_LOCK: return Key::NumLock;

        case GLFW_KEY_LEFT_SHIFT: return Key::LeftShift;
        case GLFW_KEY_RIGHT_SHIFT: return Key::RightShift;
        case GLFW_KEY_LEFT_CONTROL: return Key::LeftCtrl;
        case GLFW_KEY_RIGHT_CONTROL: return Key::RightCtrl;
        case GLFW_KEY_LEFT_ALT: return Key::LeftAlt;
        case GLFW_KEY_RIGHT_ALT: return Key::RightAlt;
        case GLFW_KEY_LEFT_SUPER: return Key::LeftMeta;
        case GLFW_KEY_RIGHT_SUPER: return Key::RightMeta;
        case GLFW_KEY_MENU: return Key::Menu;

        case GLFW_KEY_WORLD_1: return Key::World1;
        case GLFW_KEY_WORLD_2: return Key::World2;

        case GLFW_KEY_UNKNOWN: return Key::Unknown;
        default: return Key::Unknown;
    }
}

MouseButton toMouseButton(int glfwButton) noexcept
{
    switch (glfwButton)
    {
        case GLFW_MOUSE_BUTTON_LEFT: return MouseButton::Left;
        case GLFW_MOUSE_BUTTON_RIGHT: return MouseButton::Right;
        case GLFW_MOUSE_BUTTON_MIDDLE: return MouseButton::Middle;
        case GLFW_MOUSE_BUTTON_4: return MouseButton::XButton1;
        case GLFW_MOUSE_BUTTON_5: return MouseButton::XButton2;
        case GLFW_MOUSE_BUTTON_6: return MouseButton::Button6;
        case GLFW_MOUSE_BUTTON_7: return MouseButton::Button7;
        case GLFW_MOUSE_BUTTON_8: return MouseButton::Button8;
        default: return MouseButton::Unknown;
    }
}

KeyAction toAction(int glfwAction) noexcept
{
    switch (glfwAction)
    {
        case GLFW_PRESS: return KeyAction::Pressed;
        case GLFW_RELEASE: return KeyAction::Released;
        case GLFW_REPEAT: return KeyAction::Repeat;
        default: return KeyAction::Unknown;
    }
}
}