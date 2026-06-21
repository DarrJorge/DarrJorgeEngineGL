#pragma once

#include <string>
#include <cstdint>
#include <glad/glad.h>
#include <unordered_map>
#include "Render/RHI/IShader.h"

namespace DarrJorge
{
class GLShader final : public IShader
{
public:
    explicit GLShader(const std::string& vertexSourceCode, const std::string& fragmentSourceCode);
    ~GLShader() override;

    void bind() const override;
    void unbind() const override;

    void setInt(std::string_view name, int value) override;
    void setFloat(std::string_view name, float value) override;

    void setVec3(std::string_view name, float x, float y, float z) override;
    void setVec4(std::string_view name, float x, float y, float z, float w) override;
    void setMat4(std::string_view name, const float* matrix) override;

private:
    GLint getUniformLocation(std::string_view name);

private:
    GLuint m_shaderProgram;

    mutable std::unordered_map<std::string, GLint> m_uniformCache;
};
}  // namespace DarrJorge