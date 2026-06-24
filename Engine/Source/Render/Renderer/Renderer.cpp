#include "Renderer.h"
#include <glad/glad.h>
#include "Log/Log.h"
#include "Render/RHI/IBuffer.h"
#include "Render/RHI/IVertexArray.h"
#include "RenderCommand.h"
#include "Render/OpenGL/GLRenderDevice.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

using namespace DarrJorge;

DEFINE_LOG_CATEGORY_STATIC(LogRenderer);

namespace
{
static const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec4 aColor;
        out vec4 uColor;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main()
        {
            uColor = aColor;
            gl_Position = projection * view * model * vec4(aPos, 1.0);
        }      
    )";

static const char* fragmentShaderSource = R"(
        #version 330 core
        in vec4 uColor;
        out vec4 FragColor;
        uniform vec3 ourColor;
        void main()
        {
            FragColor = uColor;
        }
    )";
}  // namespace

Renderer::Renderer()
{
    LOG(LogRenderer, Display, "Renderer construct ");

    m_camera.setPerspective(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);
    m_camera.setPosition({0.0f, 0.0f, 3.0f});

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    // clang-format off
    float vertices[] = {
    // Front (0-3)
     0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, // 0
     0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, // 1
    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, // 2
    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, // 3

    // Back (4-7)
     0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, // 4
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, // 5
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, // 6
     0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, // 7

    // Left (8-11)
    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, // 8
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, // 9
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, // 10
    -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, // 11

    // Right (12-15)
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 1.0f, // 12
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, // 13
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, // 14
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 1.0f, // 15

    // Top (16-19)
     0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f, // 16
    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f, // 17
    -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, // 18
     0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, // 19

    // Bottom (20-23)
     0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, // 20
     0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, // 21
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, // 22
    -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, // 23
};
    // clang-format on

    uint32_t indices[] = {
        0, 1, 3, 1, 2, 3,        // Front
        4, 5, 7, 5, 6, 7,        // Back
        8, 9, 11, 9, 10, 11,     // Left
        12, 13, 15, 13, 14, 15,  // Right
        16, 17, 19, 17, 18, 19,  // Top
        20, 21, 23, 21, 22, 23   // Bottom
    };

    auto renderDevice = std::make_unique<GLRenderDevice>();
    m_vertexArray = renderDevice->createVertexArray();

    m_shader = renderDevice->createShaderProgram(vertexShaderSource, fragmentShaderSource);

    auto vertexBuffer = renderDevice->createVertexBuffer(vertices, sizeof(vertices));
    auto indexBuffer = renderDevice->createIndexBuffer(indices, sizeof(indices));

    VertexLayout layout = {{VertexSemantic::Position, VertexElementType::Float3}, {VertexSemantic::Color, VertexElementType::Float4}};

    vertexBuffer->setLayout(layout);

    m_vertexArray->addVertexBuffer(vertexBuffer);
    m_vertexArray->setIndexBuffer(indexBuffer);
    m_vertexArray->bind();
    m_shader->bind();
}

Renderer::~Renderer()
{
    m_vertexArray->unbind();
    m_shader->unbind();
}

void Renderer::tick(float dt)
{
    RenderCommand::setClearColor({0.2f, 0.3f, 0.3f, 1.0f});
    RenderCommand::clear();

    m_rotation += dt;

    glm::mat4 model(1.0f);
    model = glm::rotate(model, m_rotation, glm::vec3(1.0f, 1.0f, 0.0f));
    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1280 / (float)720, 0.1f, 100.0f);

    m_shader->setMat4("model", glm::value_ptr(model));
    m_shader->setMat4("view", glm::value_ptr(m_camera.viewMatrix()));
    m_shader->setMat4("projection", glm::value_ptr(m_camera.projectionMatrix()));

    RenderCommand::drawIndexed(m_vertexArray);
}