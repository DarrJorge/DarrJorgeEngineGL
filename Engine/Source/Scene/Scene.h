#pragma once

#include <vector>
#include <memory>

namespace DarrJorge
{
class Entity;
class CameraComponent;

class Scene
{
public:
    void addObject(std::shared_ptr<Entity> entity);
    void update(float deltaTime);

    [[nodiscard]] const std::vector<std::shared_ptr<Entity>>& entities() const;

    void setActiveCamera(std::shared_ptr<Entity> cameraEntity);
    [[nodiscard]] CameraComponent* activeCamera() const;

    void onResize(int width, int height);

private:
    std::vector<std::shared_ptr<Entity>> m_entities;
    std::shared_ptr<Entity> m_activeCameraEntity;
};
};