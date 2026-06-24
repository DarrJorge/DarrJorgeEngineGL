#pragma once

#include <string>
#include <cstdint>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

namespace DarrJorge
{
class IShader;
class IVertexArray;

class Transform
{
public:
    

private:
    void updateModelMatrix();

    glm::vec3 m_position{0.0f};
    glm::quat m_rotation{1.0f, 0.0f, 0.0f, 0.0f};
    glm::vec3 m_scale{1.0f};

    glm::mat4 m_matrix{1.0f};
    bool m_dirty{true};
};
}  // namespace DarrJorge