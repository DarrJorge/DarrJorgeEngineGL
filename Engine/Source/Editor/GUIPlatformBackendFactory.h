#pragma once

#include <memory>

namespace DarrJorge
{
class IWindow;
class IGUIPlatformBackend;

class GUIPlatformBackendFactory
{
public:
    static std::unique_ptr<IGUIPlatformBackend> Create(IWindow& window);
};
}  // namespace DarrJorge
