#include "MaterialFactory.h"
#include "Material.h"
#include "ShaderFactory.h"
#include "TextureFactory.h"
#include "EngineConfig.h"

using namespace DarrJorge;

std::shared_ptr<Material> MaterialFactory::createDefault()
{
    auto shader = ShaderFactory::createShader(
        std::string(ENGINE_RESOURCES_DIR) + "/Shaders/vertex.shader",
        std::string(ENGINE_RESOURCES_DIR) + "/Shaders/fragment.shader");

    auto texture = TextureFactory::createFromFile(std::string(ENGINE_RESOURCES_DIR) + "/Textures/brick.png");

    return std::make_shared<Material>(shader, texture);
}
