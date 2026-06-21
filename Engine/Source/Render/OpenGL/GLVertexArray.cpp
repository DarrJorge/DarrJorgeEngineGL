#include "GLVertexArray.h"
#include "Render/RHI/IBuffer.h"
#include "Log/Log.h"

using namespace DarrJorge;

namespace
{
GLenum ToGLType(VertexElementType type)
{
    switch (type)
    {
        case VertexElementType::Float:
        case VertexElementType::Float2:
        case VertexElementType::Float3:
        case VertexElementType::Float4:
        case VertexElementType::Mat3:
        case VertexElementType::Mat4: return GL_FLOAT;

        case VertexElementType::Int:
        case VertexElementType::Int2:
        case VertexElementType::Int3:
        case VertexElementType::Int4: return GL_INT;
    }

    return GL_FLOAT;
}

GLint GetComponentCount(VertexElementType type)
{
    switch (type)
    {
        case VertexElementType::Float:
        case VertexElementType::Int: return 1;

        case VertexElementType::Float2:
        case VertexElementType::Int2: return 2;

        case VertexElementType::Float3:
        case VertexElementType::Int3: return 3;

        case VertexElementType::Float4:
        case VertexElementType::Int4: return 4;

        default: return 0;
    }
}

GLuint GetAttributeLocation(VertexSemantic semantic)
{
    switch (semantic)
    {
        case VertexSemantic::Position: return 0;
        case VertexSemantic::Color: return 1;
        case VertexSemantic::Normal: return 2;
        case VertexSemantic::TexCoord: return 3;
        case VertexSemantic::Tangent: return 4;
        case VertexSemantic::Bitangent: return 5;
    }

    return 0;
}
}  // namespace

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

    for (const auto& element : vertexBuffer->getLayout())
    {
        const GLuint location = GetAttributeLocation(element.semantic);
        const GLint componentCount = GetComponentCount(element.elementType);
        const GLenum glType = ToGLType(element.elementType);

        LOG(LogGLVertexArray, Display, "Setting vertex attribute: location={}, componentCount={}, glType={}, stride={}, offset={}",
            location, componentCount, glType, stride, element.offset);

        glVertexAttribPointer(
            location, componentCount, glType, GL_FALSE, stride, reinterpret_cast<void*>(static_cast<uintptr_t>(element.offset)));
        glEnableVertexAttribArray(location);
    }

    m_vertexBuffers.push_back(vertexBuffer);
}

void GLVertexArray::setIndexBuffer(const std::shared_ptr<IIndexBuffer>& indexBuffer)
{
    m_indexBuffer = indexBuffer;
    m_indexBuffer->bind();
}
