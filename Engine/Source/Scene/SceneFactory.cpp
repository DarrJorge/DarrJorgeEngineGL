#include "SceneFactory.h"
#include "Scene.h"
#include "Entity.h"
#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"
#include "Components/MeshRendererComponent.h"
#include "Components/RotatorComponent.h"
#include "Resource/MeshFactory.h"

using namespace DarrJorge;

std::unique_ptr<Scene> SceneFactory::createDemoScene()
{
    auto scene = std::make_unique<Scene>();

    // TODO need replace begin
    std::shared_ptr<Entity> cube = std::make_shared<Entity>();
    cube->addComponent<TransformComponent>();
    auto str = MeshFactory::createCube();
    cube->addComponent<MeshRendererComponent>(str.mesh, str.material);
    cube->addComponent<RotatorComponent>(glm::vec3{glm::radians(20.0f), glm::radians(45.0f), 0.0f});
    scene->addObject(cube);

    std::shared_ptr<Entity> cameraEntity = std::make_shared<Entity>();
    cameraEntity->addComponent<CameraComponent>();
    scene->addObject(cameraEntity);
    scene->setActiveCamera(cameraEntity);
    // end

    return scene;
}
