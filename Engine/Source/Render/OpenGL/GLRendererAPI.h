#pragma once

#include "Render/Renderer/RendererAPI.h"

namespace DarrJorge
{
class VertexArray;

class GLRendererAPI final : public RendererAPI
{
public:
    virtual void setClearColor(const Math::Vec4& color) override;
    virtual void clear() override;
    virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
};
}  // namespace DarrJorge
