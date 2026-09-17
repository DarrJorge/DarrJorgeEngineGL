#include "TextureFactory.h"
#include "Render/RHI/ITexture.h"
#include "Render/RHI/RenderDevice.h"
#include "Render/RHI/RenderDeviceFactory.h"
#include "Log/Log.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace DarrJorge;

DEFINE_LOG_CATEGORY_STATIC(LogTextureFactory);

std::shared_ptr<ITexture> TextureFactory::createFromFile(const std::string& path)
{
    int width = 0;
    int height = 0;
    int sourceChannels = 0;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels = stbi_load(path.c_str(), &width, &height, &sourceChannels, STBI_rgb_alpha);

    if (!pixels)
    {
        LOG(LogTextureFactory, Error, "Failed to load texture: {} ({})", path, stbi_failure_reason());
        return nullptr;
    }

    auto renderDevice = RenderDeviceFactory::Create();
    auto texture = renderDevice->createTexture(pixels, static_cast<uint32_t>(width), static_cast<uint32_t>(height), TextureFormat::RGBA8);

    stbi_image_free(pixels);

    return texture;
}
