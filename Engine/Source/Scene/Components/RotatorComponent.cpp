#include "RotatorComponent.h"
#include "TransformComponent.h"
#include "Scene/Entity.h"

using namespace DarrJorge;

RotatorComponent::RotatorComponent(const glm::vec3& angularVelocityRadiansPerSecond)
    : m_angularVelocity(angularVelocityRadiansPerSecond)
{
}

void RotatorComponent::update(float deltaTime)
{
    if (auto* transform = owner()->getComponent<TransformComponent>())
    {
        transform->rotate(m_angularVelocity * deltaTime);
    }
}
