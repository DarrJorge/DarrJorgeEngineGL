#pragma once

#include "Component.h"
#include <glm/glm.hpp>

namespace DarrJorge
{
class LightComponent : public ComponentBase<LightComponent>
{
public:
    explicit LightComponent(const glm::vec3& direction = {-0.3f, -1.0f, -0.4f},
        const glm::vec3& color = {1.0f, 1.0f, 1.0f}, float ambientStrength = 0.15f);

    void setDirection(const glm::vec3& direction);
    void setColor(const glm::vec3& color);
    void setAmbientStrength(float strength);

    [[nodiscard]] const glm::vec3& direction() const { return m_direction; }
    [[nodiscard]] const glm::vec3& color() const { return m_color; }
    [[nodiscard]] float ambientStrength() const { return m_ambientStrength; }

    [[nodiscard]] std::string_view typeName() const override { return "Light"; }

private:
    glm::vec3 m_direction;
    glm::vec3 m_color;
    float m_ambientStrength;

};
}