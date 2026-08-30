#pragma once

#include <memory>

namespace DarrJorge
{
class Mesh;
class Material;

struct MeshAndMaterial
{
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Material> material;
};

class MeshFactory
{
public:
    static MeshAndMaterial createCube();
};
}