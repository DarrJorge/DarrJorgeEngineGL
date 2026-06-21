#pragma once

#include <memory>

namespace DarrJorge
{
class IShader;
class IVertexBuffer;
class IIndexBuffer;
class IVertexArray;

enum class BufferUsage
{
    Static,
    Dynamic,
    Stream
};

class RenderDevice
{
public:
    virtual ~RenderDevice() = default;
    virtual std::shared_ptr<IShader> createShaderProgram(const std::string& vertexSourceCode, const std::string& fragmentSourceCode) = 0;
    virtual std::shared_ptr<IVertexBuffer> createVertexBuffer(
        const void* data, uint32_t count, BufferUsage usage = BufferUsage::Static) = 0;
    virtual std::shared_ptr<IIndexBuffer> createIndexBuffer(
        const uint32_t* data, uint32_t count, BufferUsage usage = BufferUsage::Static) = 0;
    virtual std::shared_ptr<IVertexArray> createVertexArray() = 0;
};
}  // namespace DarrJorge