#pragma once

#include <memory>

namespace DarrJorge
{
class IVertexArray;
class RenderDevice;

class Renderer final
{
public:
    Renderer();
    ~Renderer();

    void tick(float dt);

private:
    std::shared_ptr<IVertexArray> m_vertexArray;
    std::shared_ptr<RenderDevice> m_renderDevice;
};
}  // namespace DarrJorge