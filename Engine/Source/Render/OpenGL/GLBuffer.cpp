#include "GLBuffer.h"
#include <glad/glad.h>
#include "Log/Log.h"
using namespace DarrJorge;

DEFINE_LOG_CATEGORY_STATIC(LogOpenGLBuffer);

// Vertex Buffer

GLVertexBuffer::GLVertexBuffer(float* vertices, uint32_t size)
    : m_vertices(vertices), m_size(size)
{
    LOG(LogOpenGLBuffer, Display, "GLVertexBuffer constructor ");
    glGenBuffers(1, &m_VBO);
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
    glBufferData(GL_ARRAY_BUFFER, m_size, m_vertices, GL_STATIC_DRAW);
}

void GLVertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLVertexBuffer::setLayout(const VertexLayout& layout)
{
    m_layout = layout;

    for (auto elem : m_layout)
    {
        LOG(LogOpenGLBuffer, Display, "LogOpenGLBuffer element ");
    }
}

// Index Buffer

GLIndexBuffer::GLIndexBuffer(uint32_t * indices, uint32_t count)
    : m_indices(indices), m_count(count)
{
    glGenBuffers(1, &m_EBO);
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(uint32_t), m_indices, GL_STATIC_DRAW);
}

void GLIndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}