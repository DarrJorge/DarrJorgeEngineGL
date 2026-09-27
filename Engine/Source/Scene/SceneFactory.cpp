#include "SceneFactory.h"
#include "Scene.h"
#include "Entity.h"
#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"
#include "Components/MeshRendererComponent.h"
#include "Components/RotatorComponent.h"
#include "Components/CameraControllerComponent.h"
#include "Resource/MeshFactory.h"
#include "Resource/MaterialFactory.h"

#include <format>

using namespace DarrJorge;

namespace
{
void createCube(Scene& scene, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material, const glm::vec3& position)
{
    std::shared_ptr<Entity> cube = std::make_shared<Entity>();
    cube->setName(std::format("Cube ({}, {})", static_cast<int>(position.x), static_cast<int>(position.z)));

    auto& transform = cube->addComponent<TransformComponent>();
    transform.setPosition(position);

    cube->addComponent<MeshRendererComponent>(mesh, material);
    cube->addComponent<RotatorComponent>(glm::vec3{glm::radians(20.0f), glm::radians(45.0f), 0.0f});

    scene.addObject(cube);
}
}  // namespace

std::unique_ptr<Scene> SceneFactory::createDemoScene()
{
    auto scene = std::make_unique<Scene>();

    // TODO need replace begin
    auto mesh = MeshFactory::createCube();
    auto material = MaterialFactory::createDefault();

    constexpr float spacing = 3.0f;
    constexpr int gridExtent = 1;
    for (int x = -gridExtent; x <= gridExtent; ++x)
    {
        for (int z = -gridExtent; z <= gridExtent; ++z)
        {
            createCube(*scene, mesh, material, glm::vec3{x * spacing, 0.0f, z * spacing});
        }
    }

    std::shared_ptr<Entity> cameraEntity = std::make_shared<Entity>();
    cameraEntity->setName("Camera");

    auto& camera = cameraEntity->addComponent<CameraComponent>();
    camera.setPosition({0.0f, 2.0f, 8.0f});

    cameraEntity->addComponent<CameraControllerComponent>();
    scene->addObject(cameraEntity);
    scene->setActiveCamera(cameraEntity);
    // end

    return scene;
}
