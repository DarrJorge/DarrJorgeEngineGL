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

    void rotate(float deltaYawDegrees, float deltaPitchDegrees);

    [[nodiscard]] const glm::vec3& position() const;
    [[nodiscard]] const glm::vec3& forward() const;
    [[nodiscard]] glm::vec3 right() const;

private:
    Camera m_camera;
};
}  // namespace DarrJorge
