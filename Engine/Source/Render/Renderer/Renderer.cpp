#include "Renderer.h"
#include <glad/glad.h>
#include "Log/Log.h"
#include "Render/RHI/IBuffer.h"
#include "Render/RHI/VertexArray.h"
#include "Render/RHI/Shader.h"
#include "RenderCommand.h"
#include "Render/OpenGL/GLRenderDevice.h"

using namespace DarrJorge;

DEFINE_LOG_CATEGORY_STATIC(LogRenderer);

namespace
{
static const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec4 aColor;
        out vec4 uColor;
        void main()
        {
            uColor = aColor;
            gl_Position = vec4(aPos, 1.0);
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

    Shader shader(vertexShaderSource, fragmentShaderSource);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,  // top right
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // bottom left
        -0.5f, 0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f   // top left
    };
    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 2,  // first Triangle
        1, 2, 3   // second Triangle
    };

    auto renderDevice = std::make_unique<GLRenderDevice>();
    m_vertexArray = renderDevice->createVertexArray();
    auto vertexBuffer = renderDevice->createVertexBuffer(vertices, sizeof(vertices));
    auto indexBuffer = renderDevice->createIndexBuffer(indices, sizeof(indices));

    VertexLayout layout = {{0, GL_FLOAT, 3}, {1, GL_FLOAT, 4}};
    vertexBuffer->setLayout(layout);

    m_vertexArray->addVertexBuffer(vertexBuffer);
    m_vertexArray->setIndexBuffer(indexBuffer);
    m_vertexArray->bind();
}

Renderer::~Renderer()
{
    m_vertexArray->unbind();
}

void Renderer::tick(float dt)
{
    RenderCommand::setClearColor({0.2f, 0.3f, 0.3f, 1.0f});
    RenderCommand::clear();

    // int vertexColorLoc = glGetUniformLocation(shaderProgram, "ourColor");
    // glUniform3f(vertexColorLoc, 0.0f, 1.0f, 0.0f);

    RenderCommand::drawIndexed(m_vertexArray);
}