#pragma once

#include <memory>

namespace DarrJorge
{
class Material;

class MaterialFactory
{
public:
    static std::shared_ptr<Material> createDefault();
};
}  // namespace DarrJorge
