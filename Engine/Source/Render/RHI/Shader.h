#pragma once

#include <string>
#include <cstdint>
#include <glad/glad.h>

namespace DarrJorge
{
class Shader
{
public:
    explicit Shader(const std::string& vertexSourceCode, const std::string& fragmentSourceCode);
    ~Shader();

private:
    uint32_t m_shaderProgram;
};
}  // namespace DarrJorge