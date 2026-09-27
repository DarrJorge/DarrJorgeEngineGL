#pragma once

namespace DarrJorge
{
class IGUIPlatformBackend
{
public:
    virtual ~IGUIPlatformBackend() = default;

    virtual void newFrame() = 0;
};
}  // namespace DarrJorge
