#pragma once

#include "Component.h"
#include "Event/InputEvent.h"

#include <array>
#include <glm/glm.hpp>

namespace DarrJorge
{
class CameraComponent;

class CameraControllerComponent : public ComponentBase<CameraControllerComponent>
{
public:
    explicit CameraControllerComponent(float moveSpeed = 3.0f, float lookSensitivity = 0.1f);

    void update(float deltaTime) override;

    void onKeyEvent(KeyCode key, KeyAction action);
    void onMouseMove(double x, double y);

    [[nodiscard]] std::string_view typeName() const override { return "CameraController"; }

private:
    float m_moveSpeed;
    float m_lookSensitivity;

    std::array<bool, static_cast<size_t>(KeyCode::Count)> m_keyDown{};

    bool m_hasLastMouse = false;
    double m_lastMouseX = 0.0;
    double m_lastMouseY = 0.0;

    CameraComponent* m_cameraComponent{nullptr};
};
}  // namespace DarrJorge
