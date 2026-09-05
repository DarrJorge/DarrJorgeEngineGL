#include "MeshFactory.h"
#include "Resource/Mesh.h"
#include "Resource/Material.h"
#include "Render/RHI/IBuffer.h"
#include "Render/RHI/IVertexArray.h"
#include "Render/RHI/RenderDeviceFactory.h"
#include "Render/RHI/IShader.h"
#include "Render/RHI/RenderDevice.h"

#include <memory>
#include <cstdint>

using namespace DarrJorge;

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

MeshAndMaterial MeshFactory::createCube()
{
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

    auto renderDevice = RenderDeviceFactory::Create();
    auto vertexArray = renderDevice->createVertexArray();
    std::shared_ptr mesh = std::make_shared<Mesh>(vertexArray);

    auto shader = renderDevice->createShaderProgram(vertexShaderSource, fragmentShaderSource);

    auto vertexBuffer = renderDevice->createVertexBuffer(vertices, sizeof(vertices));
    auto indexBuffer = renderDevice->createIndexBuffer(indices, std::size(indices));

    VertexLayout layout = {{VertexSemantic::Position, VertexElementType::Float3}, {VertexSemantic::Color, VertexElementType::Float4}};

    vertexBuffer->setLayout(layout);

    vertexArray->addVertexBuffer(vertexBuffer);
    vertexArray->setIndexBuffer(indexBuffer);
    vertexArray->bind();

    shader->bind();

    std::shared_ptr<Material> mat = std::make_shared<Material>(shader);

    MeshAndMaterial str;
    str.mesh = mesh;
    str.material = mat;

    return str;
}
