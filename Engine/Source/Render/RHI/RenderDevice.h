#pragma once

#include <memory>

namespace DarrJorge
{
class IVertexBuffer;
class IIndexBuffer;
class VertexArray;

class RenderDevice
{
public:
    virtual ~RenderDevice() = default;
    virtual std::shared_ptr<IVertexBuffer> createVertexBuffer(float* vertices, uint32_t size) = 0;
    virtual std::shared_ptr<IIndexBuffer> createIndexBuffer(uint32_t* indices, uint32_t size) = 0;
    virtual std::shared_ptr<VertexArray> createVertexArray() = 0;
};
}