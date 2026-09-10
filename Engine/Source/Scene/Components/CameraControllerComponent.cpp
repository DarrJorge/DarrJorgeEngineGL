#include "CameraControllerComponent.h"
#include "CameraComponent.h"
#include "Scene/Entity.h"

using namespace DarrJorge;

CameraControllerComponent::CameraControllerComponent(float moveSpeed, float lookSensitivity)
    : m_moveSpeed(moveSpeed), m_lookSensitivity(lookSensitivity)
{
}

void CameraControllerComponent::update(float deltaTime)
{
    if (!m_cameraComponent)
    {
        m_cameraComponent = owner()->getComponent<CameraComponent>();
        if (!m_cameraComponent) return;
    }

    glm::vec3 move{0.0f};

    if (m_keyDown[static_cast<size_t>(KeyCode::W)]) move += m_cameraComponent->forward();
    if (m_keyDown[static_cast<size_t>(KeyCode::S)]) move -= m_cameraComponent->forward();
    if (m_keyDown[static_cast<size_t>(KeyCode::D)]) move += m_cameraComponent->right();
    if (m_keyDown[static_cast<size_t>(KeyCode::A)]) move -= m_cameraComponent->right();

    if (glm::length(move) > 0.0f)
    {
        m_cameraComponent->setPosition(m_cameraComponent->position() + glm::normalize(move) * m_moveSpeed * deltaTime);
    }
}

void CameraControllerComponent::onKeyEvent(KeyCode key, KeyAction action)
{
    if (key == KeyCode::Unknown || key == KeyCode::Count) return;

    m_keyDown[static_cast<size_t>(key)] = (action == KeyAction::Pressed);
}

void CameraControllerComponent::onMouseMove(double x, double y)
{
    if (!m_hasLastMouse)
    {
        m_lastMouseX = x;
        m_lastMouseY = y;
        m_hasLastMouse = true;
        return;
    }

    const float deltaX = static_cast<float>(x - m_lastMouseX);
    const float deltaY = static_cast<float>(y - m_lastMouseY);

    m_lastMouseX = x;
    m_lastMouseY = y;

    if (m_cameraComponent != nullptr)
    {
        m_cameraComponent->rotate(deltaX * m_lookSensitivity, -deltaY * m_lookSensitivity);
    }
}
