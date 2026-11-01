#pragma once

#include "Event/InputEvent.h"

namespace DarrJorge::KeyMapper
{
[[nodiscard]] Key toKey(int glfwKey) noexcept;
[[nodiscard]] MouseButton toMouseButton(int glfwButton) noexcept;
[[nodiscard]] KeyAction toAction(int glfwAction) noexcept;
}