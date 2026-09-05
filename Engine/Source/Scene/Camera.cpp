#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace DarrJorge;

Camera::Camera()
{
    updateView();
    updateProjection();
}

const glm::mat4& Camera::viewMatrix() const
{
    return m_view;
}

const glm::mat4& Camera::projectionMatrix() const
{
    return m_projection;
}

void Camera::setPosition(const glm::vec3& position)
{
    m_position = position;
    updateView();
}

void Camera::setPerspective(float fovDegrees, float aspectRatio, float nearPlane, float farPlane)
{
    m_fov = fovDegrees;
    m_aspectRatio = aspectRatio;
    m_nearPlane = nearPlane;
    m_farPlane = farPlane;

    updateProjection();
}

void Camera::updateView()
{
    m_view = glm::lookAt(m_position, m_position + c_forward, c_up);
}

void Camera::updateProjection()
{
    m_projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);
}

void Camera::setAspectRatio(float aspect)
{
    m_aspectRatio = aspect;
}