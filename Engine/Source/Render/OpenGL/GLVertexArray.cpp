#include "GLVertexArray.h"
#include "Render/RHI/IBuffer.h"
#include "Log/Log.h"

using namespace DarrJorge;

DEFINE_LOG_CATEGORY_STATIC(LogGLVertexArray);

GLVertexArray::GLVertexArray()
{
    glGenVertexArrays(1, &m_vao);
}

GLVertexArray::~GLVertexArray()
{
    if (m_vao) glDeleteVertexArrays(1, &m_vao);
    glBindVertexArray(0);
}

void GLVertexArray::bind() const
{
    glBindVertexArray(m_vao);
}

void GLVertexArray::unbind() const
{
    for (const auto& vertexBuffer : m_vertexBuffers)
    {
        vertexBuffer->unbind();
    }
    glBindVertexArray(0);
    m_indexBuffer->unbind();
}

void GLVertexArray::addVertexBuffer(const std::shared_ptr<IVertexBuffer>& vertexBuffer)
{
    glBindVertexArray(m_vao);
    vertexBuffer->bind();

    const auto stride = vertexBuffer->getLayout().getStride();

    LOG(LogGLVertexArray, Display, "add vertex buffer");

    for (const auto& element : vertexBuffer->getLayout())
    {
        LOG(LogGLVertexArray, Display, "element");
        glVertexAttribPointer(
            element.index,
            element.size,
            element.type,
            GL_FALSE,
            stride * sizeof(float),
            (void*)(element.offset * sizeof(float)));
        glEnableVertexAttribArray(element.index);
    }

    m_vertexBuffers.push_back(vertexBuffer);
}

void GLVertexArray::setIndexBuffer(const std::shared_ptr<IIndexBuffer>& indexBuffer)
{
    m_indexBuffer = indexBuffer;
    m_indexBuffer->bind();
}