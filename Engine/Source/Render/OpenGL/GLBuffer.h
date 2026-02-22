#pragma once

#include <memory>
#include "Render/RHI/IBuffer.h"

namespace DarrJorge
{
class GLVertexBuffer : public IVertexBuffer
{
public:
    GLVertexBuffer(float* vertices, uint32_t size);
    virtual ~GLVertexBuffer();

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void setLayout(const VertexLayout& layout) override;
    virtual const VertexLayout& getLayout() const override { return m_layout; };

private:
    uint32_t m_VBO;
    uint32_t m_size;

    VertexLayout m_layout{};
    float* m_vertices;
};

class GLIndexBuffer : public IIndexBuffer
{
public:
    GLIndexBuffer(uint32_t* indices, uint32_t count);
    virtual ~GLIndexBuffer();

    virtual void bind() const override;
    virtual void unbind() const override;
    virtual uint32_t getCount() override { return m_count; };

private:
    uint32_t m_EBO;
    uint32_t m_count;
    uint32_t* m_indices;
};
}  // namespace DarrJorge
