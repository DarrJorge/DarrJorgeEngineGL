#pragma once

#include "Component.h"
#include <glm/glm.hpp>

namespace DarrJorge
{
class RotatorComponent : public ComponentBase<RotatorComponent>
{
public:
    explicit RotatorComponent(const glm::vec3& angularVelocityRadiansPerSecond);

    void update(float deltaTime) override;

private:
    glm::vec3 m_angularVelocity;
};
}  // namespace DarrJorge
