#pragma once

#include <vector>
#include <memory>

#include "Event/InputEvent.h"

namespace DarrJorge
{
class Entity;
class CameraComponent;
class LightComponent;

class Scene
{
public:
    void addObject(std::shared_ptr<Entity> entity);
    void update(float deltaTime);

    [[nodiscard]] const std::vector<std::shared_ptr<Entity>>& entities() const;

    void setActiveCamera(std::shared_ptr<Entity> cameraEntity);
    [[nodiscard]] CameraComponent* activeCamera() const;

    void onResize(int width, int height);
    void onKeyEvent(KeyCode key, KeyAction action);
    void onMouseMove(double x, double y);
    void onMouseButton(MouseButton button, KeyAction action);

    void setActiveLight(std::shared_ptr<Entity> lightEntity);
    [[nodiscard]] LightComponent* activeLight() const;

private:
    std::vector<std::shared_ptr<Entity>> m_entities;
    std::shared_ptr<Entity> m_activeCameraEntity;
    std::shared_ptr<Entity> m_lightEntity;
};
};