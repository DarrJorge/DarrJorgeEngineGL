#include "LightComponent.h"

using namespace DarrJorge;

LightComponent::LightComponent(const glm::vec3& direction, const glm::vec3& color, float ambientStrength)
 : m_direction(glm::normalize(direction)), m_color(color), m_ambientStrength(ambientStrength)
{}

void LightComponent::setDirection(const glm::vec3& direction)
{
    m_direction = glm::normalize(direction);
}

void LightComponent::setColor(const glm::vec3& color)
{
    m_color = color;
}

void LightComponent::setAmbientStrength(float strength)
{
    m_ambientStrength = strength;
}
