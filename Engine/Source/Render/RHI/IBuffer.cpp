#include "IBuffer.h"

using namespace DarrJorge;

VertexLayout::VertexLayout(const std::initializer_list<VertexElement>& elements) : m_elements(elements)
{
    calculateOffsetAndStride();
}

void VertexLayout::calculateOffsetAndStride()
{
    uint32_t offset = 0;
    m_stride = 0;

    for (auto& element : m_elements)
    {
        element.offset = offset;
        offset += element.size;
        m_stride += element.size;
    }
}