#pragma once

#include "Core/Utility.h"

namespace DarrJorge
{
class IShader : public NonCopyable
{
public:
    virtual ~IShader() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void setInt(std::string_view name, int value) = 0;
    virtual void setFloat(std::string_view name, float value) = 0;

    virtual void setVec3(std::string_view name, float x, float y, float z) = 0;
    virtual void setVec4(std::string_view name, float x, float y, float z, float w) = 0;
    virtual void setMat4(std::string_view name, const float* matrix) = 0;
};
}  // namespace DarrJorge