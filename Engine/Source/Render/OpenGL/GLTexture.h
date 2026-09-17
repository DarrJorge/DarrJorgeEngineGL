#pragma once

#include "Render/RHI/ITexture.h"
#include <glad/glad.h>

namespace DarrJorge
{
class GLTexture final : public ITexture
{
public:
    GLTexture(const void* pixels, uint32_t width, uint32_t height, TextureFormat format);
    ~GLTexture() override;

    void bind(uint32_t slot = 0) const override;
    void unbind() const override;

    [[nodiscard]] uint32_t width() const override { return m_width; }
    [[nodiscard]] uint32_t height() const override { return m_height; }

private:
    GLuint m_textureId{0};
    uint32_t m_width{0};
    uint32_t m_height{0};
};
}  // namespace DarrJorge
