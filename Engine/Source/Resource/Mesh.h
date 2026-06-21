#pragma once

#include <string>
#include <cstdint>
#include <glad/glad.h>

namespace DarrJorge
{
class IShader;
class IVertexArray;

class Mesh
{
public:
    Mesh(std::shared_ptr<IVertexArray> vertexArray, std::shared_ptr<IShader> shader);

private:
    std::shared_ptr<IVertexArray> m_vertexArray;
    std::shared_ptr<IShader> m_shader;
};
}  // namespace DarrJorge