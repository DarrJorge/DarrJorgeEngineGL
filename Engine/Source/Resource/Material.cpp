#include "Material.h"

using namespace DarrJorge;

Material::Material(std::shared_ptr<IShader> shader, std::shared_ptr<ITexture> texture)
    : m_shader(std::move(shader)), m_texture(std::move(texture))
{}

IShader& Material::shader()
{
    return *m_shader;
}

const IShader& Material::shader() const
{
    return *m_shader;
}

ITexture* Material::texture() const
{
    return m_texture.get();
}
