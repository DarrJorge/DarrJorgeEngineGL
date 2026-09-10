#include "CameraComponent.h"

using namespace DarrJorge;

void CameraComponent::setPosition(const glm::vec3& position)
{
    m_camera.setPosition(position);
}

void CameraComponent::setPerspective(float fovDegrees, float aspectRatio, float nearPlane, float farPlane)
{
    m_camera.setPerspective(fovDegrees, aspectRatio, nearPlane, farPlane);
}

const glm::mat4& CameraComponent::viewMatrix() const
{
    return m_camera.viewMatrix();
}

const glm::mat4& CameraComponent::projectionMatrix() const
{
    return m_camera.projectionMatrix();
}

void CameraComponent::setAspectRatio(float aspectRatio)
{
    m_camera.setAspectRatio(aspectRatio);
}

void CameraComponent::rotate(float deltaYawDegrees, float deltaPitchDegrees)
{
    m_camera.rotate(deltaYawDegrees, deltaPitchDegrees);
}

const glm::vec3& CameraComponent::position() const
{
    return m_camera.position();
}

const glm::vec3& CameraComponent::forward() const
{
    return m_camera.forward();
}

glm::vec3 CameraComponent::right() const
{
    return m_camera.right();
}
