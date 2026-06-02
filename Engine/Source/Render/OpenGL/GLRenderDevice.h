#pragma once

#include "Render/RHI/RenderDevice.h"
#include <memory>

namespace DarrJorge
{
class IVertexBuffer;
class IIndexBuffer;
class IVertexArray;

class GLRenderDevice : public RenderDevice
{
public:
    virtual std::shared_ptr<IVertexBuffer> createVertexBuffer(const void* data, uint32_t count, BufferUsage usage = BufferUsage::Static) override;
    virtual std::shared_ptr<IIndexBuffer> createIndexBuffer(const uint32_t* data, uint32_t count, BufferUsage usage = BufferUsage::Static) override;
    virtual std::shared_ptr<IVertexArray> createVertexArray() override;
};
}  // namespace DarrJorge