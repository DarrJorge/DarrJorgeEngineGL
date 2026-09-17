#include "GLTexture.h"
#include "Log/Log.h"

using namespace DarrJorge;

DEFINE_LOG_CATEGORY_STATIC(LogGLTexture);

namespace
{
GLenum ToGLInternalFormat(TextureFormat format)
{
    switch (format)
    {
        case TextureFormat::RGB8: return GL_RGB8;
        case TextureFormat::RGBA8: return GL_RGBA8;
    }
    return GL_RGBA8;
}

GLenum ToGLDataFormat(TextureFormat format)
{
    switch (format)
    {
        case TextureFormat::RGB8: return GL_RGB;
        case TextureFormat::RGBA8: return GL_RGBA;
    }
    return GL_RGBA;
}
}  // namespace

GLTexture::GLTexture(const void* pixels, uint32_t width, uint32_t height, TextureFormat format)
    : m_width(width), m_height(height)
{
    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, ToGLInternalFormat(format), static_cast<GLsizei>(width), static_cast<GLsizei>(height), 0,
        ToGLDataFormat(format), GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    LOG(LogGLTexture, Display, "Created texture {}x{}", width, height);
}

GLTexture::~GLTexture()
{
    glDeleteTextures(1, &m_textureId);
}

void GLTexture::bind(uint32_t slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
}

void GLTexture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
