#pragma once

#include "Event/InputEvent.h"
#include <format>
#include <string_view>

template<>
struct std::formatter<DarrJorge::Key> : std::formatter<std::string_view>
{
    template <class FormatContext>
    auto format(DarrJorge::Key key, FormatContext& ctx) const
    {
        return std::formatter<std::string_view>::format(DarrJorge::toString(key), ctx);
    }
};

template<>
struct std::formatter<DarrJorge::KeyAction> : std::formatter<std::string_view>
{
    template <class FormatContext>
    auto format(DarrJorge::KeyAction action, FormatContext& ctx) const
    {
        return std::formatter<std::string_view>::format(DarrJorge::toString(action), ctx);
    }
};

template<>
struct std::formatter<DarrJorge::MouseButton> : std::formatter<std::string_view>
{
    template <class FormatContext>
    auto format(DarrJorge::MouseButton button, FormatContext& ctx) const
    {
        return std::formatter<std::string_view>::format(DarrJorge::toString(button), ctx);
    }
};

template<>
struct std::formatter<DarrJorge::EventType> : std::formatter<std::string_view>
{
    template <class FormatContext>
    auto format(DarrJorge::EventType eventType, FormatContext& ctx) const
    {
        return std::formatter<std::string_view>::format(DarrJorge::toString(eventType), ctx);
    }
};