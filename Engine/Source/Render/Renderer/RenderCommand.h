#pragma once

#include <memory>
#include "Core/MathTypes.h"

namespace DarrJorge
{
class IVertexArray;
class RendererAPI;

class RenderCommand
{
public:
    static void init();

    static void drawIndexed(IVertexArray* vertexArray);
    static void setClearColor(const Math::Vec4& color);
    static void clear();

    static void setViewport(int x, int y, int width, int height);

private:
    static std::unique_ptr<RendererAPI> s_api;
};
}  // namespace DarrJorge
