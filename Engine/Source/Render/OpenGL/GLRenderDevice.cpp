#include "GLRenderDevice.h"
#include "GLShader.h"
#include "GLBuffer.h"
#include "GLVertexArray.h"

using namespace DarrJorge;

std::shared_ptr<IShader> GLRenderDevice::createShaderProgram(const std::string& vertexSourceCode, const std::string& fragmentSourceCode)
{
    return std::make_shared<GLShader>(vertexSourceCode, fragmentSourceCode);
}

std::shared_ptr<IVertexBuffer> GLRenderDevice::createVertexBuffer(const void* data, uint32_t count, BufferUsage usage)
{
    return std::make_shared<GLVertexBuffer>(data, count, usage);
}

std::shared_ptr<IIndexBuffer> GLRenderDevice::createIndexBuffer(const uint32_t* data, uint32_t count, BufferUsage usage)
{
    return std::make_shared<GLIndexBuffer>(data, count, usage);
}

std::shared_ptr<IVertexArray> GLRenderDevice::createVertexArray()
{
    return std::make_shared<GLVertexArray>();
}