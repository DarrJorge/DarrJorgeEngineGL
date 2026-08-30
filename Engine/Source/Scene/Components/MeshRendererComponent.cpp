#include "MeshRendererComponent.h"

using namespace DarrJorge;

MeshRendererComponent::MeshRendererComponent(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
    : m_mesh(std::move(mesh)), m_material(std::move(material))
{
}

Mesh& MeshRendererComponent::mesh()
{
    return *m_mesh;
}

Material& MeshRendererComponent::material()
{
    return *m_material;
}

const Mesh& MeshRendererComponent::mesh() const
{
    return *m_mesh;
}

const Material& MeshRendererComponent::material() const
{
    return *m_material;
}