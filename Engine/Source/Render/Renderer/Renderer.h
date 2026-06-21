#pragma once

#include <memory>
#include "Render/RHI/Shader.h"
#include "Core/Camera.h"

namespace DarrJorge
{
class IVertexArray;
class RenderDevice;
class IShader;

class Renderer final
{
public:
    Renderer();
    ~Renderer();

    void tick(float dt);

private:
    std::shared_ptr<IVertexArray> m_vertexArray;
    std::shared_ptr<RenderDevice> m_renderDevice;
    std::shared_ptr<IShader> m_shader;

    Camera m_camera;
    float m_rotation = 0.0f;
};
}  // namespace DarrJorge