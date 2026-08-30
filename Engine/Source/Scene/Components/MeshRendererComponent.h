#pragma once

#include "Component.h"
#include <memory>

namespace DarrJorge
{
class Mesh;
class Material;

class MeshRendererComponent : public Component
{
public:
    MeshRendererComponent(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);

    Mesh& mesh();
    Material& material();

    [[nodiscard]] const Mesh& mesh() const;
    [[nodiscard]] const Material& material() const;

private:
    std::shared_ptr<Mesh> m_mesh;
    std::shared_ptr<Material> m_material;
};
};
