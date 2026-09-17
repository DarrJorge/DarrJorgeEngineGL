#pragma once

#include <memory>
#include <string>

namespace DarrJorge
{
class ITexture;

class TextureFactory
{
public:
    static std::shared_ptr<ITexture> createFromFile(const std::string& path);
};
}  // namespace DarrJorge
