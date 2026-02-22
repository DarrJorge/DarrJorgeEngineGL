#include "GLRendererAPI.h"
#include "GLVertexArray.h"
#include "GLBuffer.h"
#include <glad/glad.h>

using namespace DarrJorge;

void GLRendererAPI::setClearColor(const Math::Vec4& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

void GLRendererAPI::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLRendererAPI::drawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
{
    glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
}