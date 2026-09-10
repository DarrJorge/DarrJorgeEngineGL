#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace DarrJorge;

Camera::Camera()
{
    updateOrientation();
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
    m_view = glm::lookAt(m_position, m_position + m_forward, c_up);
}

void Camera::updateProjection()
{
    m_projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);
}

void Camera::updateOrientation()
{
    m_pitch = glm::clamp(m_pitch, -89.0f, 89.0f);

    glm::vec3 forward;
    forward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    forward.y = sin(glm::radians(m_pitch));
    forward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_forward = glm::normalize(forward);

    updateView();
}

void Camera::setAspectRatio(float aspect)
{
    m_aspectRatio = aspect;
    updateProjection();
}

void Camera::setYawPitch(float yawDegrees, float pitchDegrees)
{
    m_yaw = yawDegrees;
    m_pitch = pitchDegrees;
    updateOrientation();
}

void Camera::rotate(float deltaYawDegrees, float deltaPitchDegrees)
{
    m_yaw += deltaYawDegrees;
    m_pitch += deltaPitchDegrees;
    updateOrientation();
}

const glm::vec3& Camera::position() const
{
    return m_position;
}

const glm::vec3& Camera::forward() const
{
    return m_forward;
}

glm::vec3 Camera::right() const
{
    return glm::normalize(glm::cross(m_forward, c_up));
}