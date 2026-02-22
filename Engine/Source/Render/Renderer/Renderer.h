#pragma once

#include <memory>

namespace DarrJorge
{
class VertexArray;

class Renderer final
{
public:
    Renderer();
    ~Renderer();

    void tick(float dt);

private:
    std::shared_ptr<VertexArray> m_vertexArray;
};
}  // namespace DarrJorge