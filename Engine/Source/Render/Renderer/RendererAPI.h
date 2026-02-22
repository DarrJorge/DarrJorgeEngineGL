#pragma once

#include <cstdint>
#include <memory>
#include "Core/MathTypes.h"

namespace DarrJorge
{
class IVertexBuffer;
class IIndexBuffer;
class VertexArray;

class RendererAPI
{
public:
    enum class API : uint8_t
    {
        None = 0,
        OpenGL
    };

public:
    virtual void setClearColor(const Math::Vec4& color) = 0;
    virtual void clear() = 0;

    virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

    inline static API getAPI() { return s_api; }

private:
    static API s_api;
};
}
