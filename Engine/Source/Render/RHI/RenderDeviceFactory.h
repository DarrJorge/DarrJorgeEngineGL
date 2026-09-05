#pragma once

#include <memory>

namespace DarrJorge
{
class RenderDevice;

class RenderDeviceFactory
{
public:
    static std::unique_ptr<RenderDevice> Create();
};
}  // namespace DarrJorge
