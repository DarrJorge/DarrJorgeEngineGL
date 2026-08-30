#pragma once

#include "Component.h"
#include <glm/glm.hpp>

namespace DarrJorge
{
class RotatorComponent : public Component
{
public:
    explicit RotatorComponent(const glm::vec3& angularVelocityRadiansPerSecond);

    void update(float deltaTime) override;

private:
    glm::vec3 m_angularVelocity;
};
}  // namespace DarrJorge
