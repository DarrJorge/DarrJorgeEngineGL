#pragma once

#include "Core/MathTypes.h"

namespace DarrJorge
{
class IVertexBuffer;
class IIndexBuffer;
class IVertexArray;

class RendererAPI
{
public:
    virtual ~RendererAPI() = default;

    virtual void init() {}

    virtual void setClearColor(const Math::Vec4& color) = 0;
    virtual void clear() = 0;

    virtual void drawIndexed(IVertexArray* vertexArray) = 0;
    virtual void setViewport(int x, int y, int width, int height) = 0;
};
}  // namespace DarrJorge
