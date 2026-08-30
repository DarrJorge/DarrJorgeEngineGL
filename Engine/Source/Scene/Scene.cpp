#include "Scene.h"
#include "Entity.h"
#include "Components/CameraComponent.h"

using namespace DarrJorge;

void Scene::addObject(std::shared_ptr<Entity> entity)
{
    m_entities.push_back(entity);
}

const std::vector<std::shared_ptr<Entity>>& Scene::entities() const
{
    return m_entities;
}

void Scene::update(float deltaTime)
{
    for (const auto& entity : m_entities)
    {
        entity->update(deltaTime);
    }
}

void Scene::setActiveCamera(std::shared_ptr<Entity> cameraEntity)
{
    m_activeCameraEntity = std::move(cameraEntity);
}

CameraComponent* Scene::activeCamera() const
{
    return m_activeCameraEntity ? m_activeCameraEntity->getComponent<CameraComponent>() : nullptr;
}
