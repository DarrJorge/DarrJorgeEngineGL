#pragma once

namespace DarrJorge
{
class IGUIRendererBackend
{
public:
    virtual ~IGUIRendererBackend() = default;

    virtual void newFrame() = 0;
    virtual void renderDrawData() = 0;
};
}  // namespace DarrJorge
