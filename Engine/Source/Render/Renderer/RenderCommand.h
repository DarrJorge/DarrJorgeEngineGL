#pragma once

#include <memory>
#include "RendererAPI.h"
#include "Core/MathTypes.h"

namespace DarrJorge
{
class VertexArray;

class RenderCommand
{
public:
    static void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
    {
        if (s_api)
        {
            s_api->drawIndexed(vertexArray);
        }
    }

    static void setClearColor(const Math::Vec4& color)
    {
        if (s_api)
        {
            s_api->setClearColor(color);
        }
    }

    static void clear()
    {
        if (s_api)
        {
            s_api->clear();
        }
    };

private:
    static RendererAPI* s_api;
};
}  // namespace DarrJorge
