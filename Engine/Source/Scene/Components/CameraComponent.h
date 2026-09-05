#pragma once

#include "Component.h"
#include "Scene/Camera.h"

namespace DarrJorge
{
class CameraComponent : public Component
{
public:
    CameraComponent() = default;

    void setPosition(const glm::vec3& position);
    void setPerspective(float fovDegrees, float aspectRatio, float nearPlane, float farPlane);

    [[nodiscard]] const glm::mat4& viewMatrix() const;
    [[nodiscard]] const glm::mat4& projectionMatrix() const;

    void setAspectRatio(float aspectRatio);

private:
    Camera m_camera;
};
}  // namespace DarrJorge
