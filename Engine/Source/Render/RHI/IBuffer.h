#pragma once

#include <cstdint>
#include <vector>

namespace DarrJorge
{
    struct VertexElement
    {
        uint32_t index;     // attribute location
        uint32_t size;      // number of components
        uint32_t type;      // data type (e.g GL_FLOAT)
        uint32_t offset;

        VertexElement(uint32_t inIndex, uint32_t inType, uint32_t inSize)
            : index(inIndex), type(inType), size(inSize), offset(0) {}
    };

    class VertexLayout
    {
    public:
        VertexLayout(const std::initializer_list<VertexElement>& elements);

        std::vector<VertexElement>::iterator begin() { return m_elements.begin(); }
        std::vector<VertexElement>::iterator end() { return m_elements.end(); }

        [[nodiscard]] const std::vector<VertexElement>::const_iterator begin() const { return m_elements.begin(); }
        [[nodiscard]] const std::vector<VertexElement>::const_iterator end() const { return m_elements.end(); }

        [[nodiscard]] uint32_t getStride() const { return m_stride; }

    private:
        std::vector<VertexElement> m_elements;
        uint32_t m_stride{0};

        void calculateOffsetAndStride();
    };

    class IVertexBuffer
    {
    public:
        virtual ~IVertexBuffer() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void setLayout(const VertexLayout& layout) = 0;
        virtual const VertexLayout& getLayout() const = 0;
    };

    class IIndexBuffer
    {
    public:
        virtual ~IIndexBuffer() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;
        virtual uint32_t getCount() = 0;
    };
}
