#pragma once

#include "Render/Renderer/RendererAPI.h"

namespace DarrJorge
{
class IVertexArray;

class GLRendererAPI final : public RendererAPI
{
public:
    void init() override;

    virtual void setClearColor(const Math::Vec4& color) override;
    virtual void clear() override;
    virtual void drawIndexed(IVertexArray* vertexArray) override;

    virtual void setViewport(int x, int y, int width, int height) override;
};
}  // namespace DarrJorge
