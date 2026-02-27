#pragma once

#include <memory>

namespace DarrJorge
{
class IVertexBuffer;
class IIndexBuffer;

class VertexArray
{
public:
    virtual ~VertexArray() {};

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void addVertexBuffer(const std::shared_ptr<IVertexBuffer>& vertexBuffer) = 0;
    virtual void setIndexBuffer(const std::shared_ptr<IIndexBuffer>& vertexBuffer) = 0;
    virtual std::shared_ptr<IIndexBuffer>& getIndexBuffer() = 0;
};
}  // namespace DarrJorge
