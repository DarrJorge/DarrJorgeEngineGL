#include "GLRenderDevice.h"
#include "Render/OpenGL/GLBuffer.h"
#include "Render/OpenGL/GLVertexArray.h"

using namespace DarrJorge;

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