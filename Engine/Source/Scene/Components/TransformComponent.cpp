#include "TransformComponent.h"

using namespace DarrJorge;

glm::mat4 TransformComponent::matrix() const
{
    glm::mat4 model{1.0f};

    model = glm::translate(model, m_position);

    model = glm::rotate(model, m_rotationEuler.x, glm::vec3(1,0,0));
    model = glm::rotate(model, m_rotationEuler.y, glm::vec3(0,1,0));
    model = glm::rotate(model, m_rotationEuler.z, glm::vec3(0,0,1));

    model = glm::scale(model, m_scale);

    return model;
}

void TransformComponent::setPosition(const glm::vec3& position)
{
    m_position = position;
}

void TransformComponent::setRotationEuler(const glm::vec3& eulerRadians)
{
    m_rotationEuler = eulerRadians;
}

void TransformComponent::rotate(const glm::vec3& deltaEulerRadians)
{
    m_rotationEuler += deltaEulerRadians;
}

void TransformComponent::setScale(const glm::vec3& scale)
{
    m_scale = scale;
}
