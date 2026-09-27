#pragma once

#include "Component.h"

//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

namespace DarrJorge
{
class TransformComponent : public ComponentBase<TransformComponent>
{
public:
    [[nodiscard]] glm::mat4 matrix() const;

    void setPosition(const glm::vec3& position);
    void setRotationEuler(const glm::vec3& eulerRadians);
    void rotate(const glm::vec3& deltaEulerRadians);
    void setScale(const glm::vec3& scale);

    [[nodiscard]] const glm::vec3& position() const { return m_position; }
    [[nodiscard]] const glm::vec3& rotationEuler() const { return m_rotationEuler; }
    [[nodiscard]] const glm::vec3& scale() const { return m_scale; }

    [[nodiscard]] std::string_view typeName() const override { return "Transform"; }

private:
    glm::vec3 m_position{0.0f};
    glm::vec3 m_rotationEuler{0.0f};
    glm::vec3 m_scale{1.0f};
};
}  // namespace DarrJorge