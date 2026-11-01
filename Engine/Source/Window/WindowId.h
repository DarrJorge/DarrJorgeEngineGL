#pragma once

#include "Core/Types.h"


namespace DarrJorge
{
struct WindowId
{
    uint32 value{0};
    constexpr explicit WindowId(uint32 id = 0) : value(id) {}

    constexpr WindowId operator++(int)
    {
        WindowId temp = *this;
        ++value;
        return temp;
    }

    constexpr auto operator<=>(const WindowId&) const = default;
};
}

namespace std
{
template <>
struct hash<DarrJorge::WindowId>
{
    size_t operator()(const DarrJorge::WindowId& id) const noexcept { return std::hash<DarrJorge::uint32>{}(id.value); }
};
}  // namespace std