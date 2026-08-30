#pragma once

#include "Component.h"

//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

namespace DarrJorge
{
class TransformComponent : public Component
{
public:
    [[nodiscard]] glm::mat4 matrix() const;

    void setPosition(const glm::vec3& position);
    void setRotationEuler(const glm::vec3& eulerRadians);
    void rotate(const glm::vec3& deltaEulerRadians);
    void setScale(const glm::vec3& scale);

private:
    glm::vec3 m_position{0.0f};
    glm::vec3 m_rotationEuler{0.0f};
    glm::vec3 m_scale{1.0f};
};
}  // namespace DarrJorge