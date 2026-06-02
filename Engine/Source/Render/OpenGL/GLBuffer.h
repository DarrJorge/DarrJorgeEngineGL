#pragma once

#include <memory>
#include "Render/RHI/IBuffer.h"
#include "../RHI/RenderDevice.h"

namespace DarrJorge
{
class GLVertexBuffer : public IVertexBuffer
{
public:
    GLVertexBuffer(const void* data, uint32_t count, BufferUsage usage);
    virtual ~GLVertexBuffer();

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void setLayout(const VertexLayout& layout) override;
    virtual const VertexLayout& getLayout() const override { return m_layout; };

private:
    uint32_t m_VBO;
    uint32_t m_size;

    VertexLayout m_layout{};
};

class GLIndexBuffer : public IIndexBuffer
{
public:
    GLIndexBuffer(const uint32_t* indices, uint32_t count, BufferUsage usage);
    virtual ~GLIndexBuffer();

    virtual void bind() const override;
    virtual void unbind() const override;
    virtual uint32_t getCount() override { return m_count; };

private:
    uint32_t m_EBO;
    uint32_t m_count;
};
}  // namespace DarrJorge
