#pragma once

#include "Event/InputEvent.h"
#include <format>
#include <string_view>

template<>
struct std::formatter<DarrJorge::Key> : std::formatter<std::string_view>
{
    auto format(DarrJorge::Key key, std::format_context& ctx) const
    {
        return std::formatter<std::string_view>::format(DarrJorge::toString(key), ctx);
    }
};

template<>
struct std::formatter<DarrJorge::KeyAction> : std::formatter<std::string_view>
{
    auto format(DarrJorge::KeyAction action, std::format_context& ctx) const
    {
        return std::formatter<std::string_view>::format(DarrJorge::toString(action), ctx);
    }
};

template<>
struct std::formatter<DarrJorge::MouseButton> : std::formatter<std::string_view>
{
    auto format(DarrJorge::MouseButton button, std::format_context& ctx) const
    {
        return std::formatter<std::string_view>::format(DarrJorge::toString(button), ctx);
    }
};

template<>
struct std::formatter<DarrJorge::EventType> : std::formatter<std::string_view>
{
    auto format(DarrJorge::EventType eventType, std::format_context& ctx) const
    {
        return std::formatter<std::string_view>::format(DarrJorge::toString(eventType), ctx);
    }
};