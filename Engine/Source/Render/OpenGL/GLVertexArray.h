#pragma once

#include <glad/glad.h>
#include <vector>
#include "Render/RHI/VertexArray.h"

namespace DarrJorge
{
class IVertexBuffer;
class IIndexBuffer;

class GLVertexArray : public VertexArray
{
public:
    GLVertexArray();
    ~GLVertexArray();

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void addVertexBuffer(const std::shared_ptr<IVertexBuffer>& vertexBuffer) override;
    virtual void setIndexBuffer(const std::shared_ptr<IIndexBuffer>& vertexBuffer) override;
    virtual std::shared_ptr<IIndexBuffer>& getIndexBuffer() override { return m_indexBuffer; };

private:
    GLuint m_vao{0};
    std::vector<std::shared_ptr<IVertexBuffer>> m_vertexBuffers;
    std::shared_ptr<IIndexBuffer> m_indexBuffer;
};
}