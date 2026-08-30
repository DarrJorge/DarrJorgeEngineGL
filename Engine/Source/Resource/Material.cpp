#include "Material.h"

using namespace DarrJorge;

Material::Material(std::shared_ptr<IShader> shader)
    : m_shader(std::move(shader))
{}

IShader& Material::shader()
{
    return *m_shader;
}

const IShader& Material::shader() const
{
    return *m_shader;
}
