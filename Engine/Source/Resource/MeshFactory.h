#pragma once

#include <memory>

namespace DarrJorge
{
class Mesh;

class MeshFactory
{
public:
    static std::shared_ptr<Mesh> createCube();
};
}