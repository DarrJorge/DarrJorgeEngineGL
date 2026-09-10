#include "Scene.h"
#include "Entity.h"
#include "Components/CameraComponent.h"
#include "Components/CameraControllerComponent.h"

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

void Scene::onResize(int width, int height)
{
    if (auto* camera = activeCamera())
    {
        const float aspect = height > 0 ? static_cast<float>(width) / static_cast<float>(height) : 1.0;
        camera->setAspectRatio(aspect);
    }
}

void Scene::onKeyEvent(KeyCode key, KeyAction action)
{
    if (auto* camera = activeCamera())
    {
        if (auto* controller = camera->owner()->getComponent<CameraControllerComponent>())
        {
            controller->onKeyEvent(key, action);
        }
    }
}

void Scene::onMouseMove(double x, double y)
{
    if (auto* camera = activeCamera())
    {
        if (auto* controller = camera->owner()->getComponent<CameraControllerComponent>())
        {
            controller->onMouseMove(x, y);
        }
    }
}
