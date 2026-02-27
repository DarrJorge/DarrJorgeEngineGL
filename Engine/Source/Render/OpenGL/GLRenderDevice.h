#pragma once

#include "Render/RHI/RenderDevice.h"
#include <memory>

namespace DarrJorge
{
class IVertexBuffer;
class IIndexBuffer;
class VertexArray;

class GLRenderDevice : public RenderDevice
{
public:
    virtual std::shared_ptr<IVertexBuffer> createVertexBuffer(float* vertices, uint32_t size) override;
    virtual std::shared_ptr<IIndexBuffer> createIndexBuffer(uint32_t* indices, uint32_t size) override;
    virtual std::shared_ptr<VertexArray> createVertexArray() override;
};
}  // namespace DarrJorge