#pragma once

#include <memory>
#include <string>

namespace DarrJorge
{
class IShader;

class ShaderFactory
{
public:
    static std::shared_ptr<IShader> createShader(const std::string& vertexPath, const std::string& fragmentPath);
};
}  // namespace DarrJorge
