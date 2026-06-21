#pragma once

#include <cstdint>
#include <vector>

namespace DarrJorge
{
enum class VertexElementType : uint8_t
{
    Float,
    Float2,
    Float3,
    Float4,

    Int,
    Int2,
    Int3,
    Int4,

    Mat3,
    Mat4
};

enum class VertexSemantic : uint8_t
{
    Position,
    Color,
    Normal,
    TexCoord,
    Tangent,
    Bitangent
};

struct VertexElement
{
    VertexSemantic semantic;        // enum to represent the semantic meaning of the vertex element
    VertexElementType elementType;  // enum to represent the type of vertex element
    uint32_t offset;

    VertexElement(VertexSemantic inSemantic, VertexElementType type) : semantic(inSemantic), elementType(type), offset(0) {}

    [[nodiscard]]
    uint32_t GetSize() const
    {
        return GetElementSize(elementType);
    }

    static constexpr uint32_t GetElementSize(VertexElementType type)
    {
        switch (type)
        {
            case VertexElementType::Float: return sizeof(float);
            case VertexElementType::Float2: return sizeof(float) * 2;
            case VertexElementType::Float3: return sizeof(float) * 3;
            case VertexElementType::Float4: return sizeof(float) * 4;

            case VertexElementType::Int: return sizeof(int32_t);
            case VertexElementType::Int2: return sizeof(int32_t) * 2;
            case VertexElementType::Int3: return sizeof(int32_t) * 3;
            case VertexElementType::Int4: return sizeof(int32_t) * 4;

            case VertexElementType::Mat3: return sizeof(float) * 3 * 3;
            case VertexElementType::Mat4: return sizeof(float) * 4 * 4;

            default: return 0;
        }
    }
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
}  // namespace DarrJorge
