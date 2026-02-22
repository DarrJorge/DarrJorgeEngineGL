#include "GLRenderDevice.h"
#include "Render/OpenGL/GLBuffer.h"
#include "Render/OpenGL/GLVertexArray.h"

using namespace DarrJorge;

std::shared_ptr<IVertexBuffer> GLRenderDevice::createVertexBuffer(float* vertices, uint32_t size)
{
    return std::make_shared<GLVertexBuffer>(vertices, size);
}

std::shared_ptr<IIndexBuffer> GLRenderDevice::createIndexBuffer(uint32_t* indices, uint32_t size)
{
    return std::make_shared<GLIndexBuffer>(indices, size);
}

std::shared_ptr<VertexArray> GLRenderDevice::createVertexArray()
{
    return std::make_shared<GLVertexArray>();
}