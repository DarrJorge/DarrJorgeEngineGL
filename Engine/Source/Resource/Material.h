#pragma once

namespace DarrJorge
{
class IShader;

class Material
{
public:
    explicit Material(std::shared_ptr<IShader> shader);

    IShader& shader();
    [[nodiscard]] const IShader& shader() const;

private:
    std::shared_ptr<IShader> m_shader;
};
}
