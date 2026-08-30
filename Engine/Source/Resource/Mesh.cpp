#include "Mesh.h"

using namespace DarrJorge;

Mesh::Mesh(std::shared_ptr<IVertexArray> vertexArray)
    : m_vertexArray(std::move(vertexArray))
{
}

IVertexArray* Mesh::vertexArray()
{
    return m_vertexArray.get();
}

const IVertexArray& Mesh::vertexArray() const
{
    return *m_vertexArray;
}
