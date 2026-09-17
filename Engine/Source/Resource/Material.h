#pragma once

#include <memory>

namespace DarrJorge
{
class IShader;
class ITexture;

class Material
{
public:
    Material(std::shared_ptr<IShader> shader, std::shared_ptr<ITexture> texture);

    IShader& shader();
    [[nodiscard]] const IShader& shader() const;

    [[nodiscard]] ITexture* texture() const;

private:
    std::shared_ptr<IShader> m_shader;
    std::shared_ptr<ITexture> m_texture;
};
}
