#include "GLBuffer.h"
#include <glad/glad.h>
#include "Log/Log.h"

using namespace DarrJorge;

DEFINE_LOG_CATEGORY_STATIC(LogOpenGLBuffer);

namespace
{
GLenum ConvertUsage(BufferUsage usage)
{
    switch (usage)
    {
        case BufferUsage::Static: return GL_STATIC_DRAW;
        case BufferUsage::Dynamic: return GL_DYNAMIC_DRAW;
        case BufferUsage::Stream: return GL_STREAM_DRAW;
    }

    return GL_STATIC_DRAW;
}
}  // namespace

// Vertex Buffer

GLVertexBuffer::GLVertexBuffer(const void* data, uint32_t count, BufferUsage usage) : m_size(count)
{
    glGenBuffers(1, &m_VBO);

    GLenum glUsage = ConvertUsage(usage);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_size, data, glUsage);
}

GLVertexBuffer::~GLVertexBuffer()
{
    glDeleteBuffers(1, &m_VBO);
    m_VBO = 0;
    m_size = 0;
}

void GLVertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
}

void GLVertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLVertexBuffer::setLayout(const VertexLayout& layout)
{
    m_layout = layout;
}

// Index Buffer

GLIndexBuffer::GLIndexBuffer(const uint32_t* indices, uint32_t count, BufferUsage usage) : m_count(count)
{
    glGenBuffers(1, &m_EBO);

    GLenum glUsage = ConvertUsage(usage);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(uint32_t), indices, glUsage);
}

GLIndexBuffer::~GLIndexBuffer()
{
    glDeleteBuffers(1, &m_EBO);
    m_EBO = 0;
    m_count = 0;
}

void GLIndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
}

void GLIndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}