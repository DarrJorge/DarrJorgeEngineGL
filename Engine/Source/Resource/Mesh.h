#pragma once

#include <string>
#include <cstdint>
#include <glad/glad.h>

namespace DarrJorge
{
class IVertexArray;

class Mesh
{
public:
    explicit Mesh(std::shared_ptr<IVertexArray> vao);

    IVertexArray* vertexArray();
    [[nodiscard]] const IVertexArray& vertexArray() const;

private:
    std::shared_ptr<IVertexArray> m_vertexArray;
};
}  // namespace DarrJorge