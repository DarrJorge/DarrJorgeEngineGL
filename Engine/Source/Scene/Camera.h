#pragma once

#include <glm/glm.hpp>

namespace DarrJorge
{
class Camera
{
public:
    Camera();

    [[nodiscard]] const glm::mat4& viewMatrix() const;
    [[nodiscard]] const glm::mat4& projectionMatrix() const;

    void setPosition(const glm::vec3& position);
    void setPerspective(float fovDegrees, float aspectRatio, float nearPlane, float farPlane);

private:
    void updateView();
    void updateProjection();

private:
    glm::vec3 m_position{0.0f, 0.0f, 3.0f};

    static constexpr glm::vec3 c_forward{0.0f, 0.0f, -1.0f};
    static constexpr glm::vec3 c_up{0.0f, 1.0f, 0.0f};

    float m_fov = 45.0f;
    float m_aspectRatio = 16.0f / 9.0f;
    float m_nearPlane = 0.1f;
    float m_farPlane = 100.0f;

    glm::mat4 m_view;
    glm::mat4 m_projection;
};
}  // namespace DarrJorge