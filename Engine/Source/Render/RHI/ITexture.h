#pragma once

#include "Core/Utility.h"
#include <cstdint>

namespace DarrJorge
{
enum class TextureFormat : uint8_t
{
    RGB8,
    RGBA8
};

class ITexture : public NonCopyable
{
public:
    virtual ~ITexture() = default;

    virtual void bind(uint32_t slot = 0) const = 0;
    virtual void unbind() const = 0;

    [[nodiscard]] virtual uint32_t width() const = 0;
    [[nodiscard]] virtual uint32_t height() const = 0;
};
}  // namespace DarrJorge
