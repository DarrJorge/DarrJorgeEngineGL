#include "Renderer.h"
#include "Log/Log.h"
#include "Render/RHI/IBuffer.h"
#include "Render/RHI/IVertexArray.h"
#include "RenderCommand.h"
#include "Scene/Scene.h"
#include "Scene/Entity.h"
#include "Scene/Components/CameraComponent.h"
#include "Scene/Components/TransformComponent.h"
#include "Scene/Components/MeshRendererComponent.h"
#include "Resource/Material.h"
#include "Resource/Mesh.h"
#include "Render/RHI/IShader.h"
#include "Render/RHI/ITexture.h"

#include <glm/gtc/type_ptr.hpp>

using namespace DarrJorge;

DEFINE_LOG_CATEGORY_STATIC(LogRenderer);

Renderer::Renderer()
{
    RenderCommand::init();

    LOG(LogRenderer, Display, "Renderer construct ");
}

Renderer::~Renderer() {}

void Renderer::beginFrame()
{
    RenderCommand::setClearColor({0.2f, 0.3f, 0.3f, 1.0f});
    RenderCommand::clear();
}

void Renderer::render(const Scene& scene)
{
    beginFrame();

    const CameraComponent* camera = scene.activeCamera();
    if (!camera)
    {
        LOG(LogRenderer, Warning, "No active camera set on Scene; skipping draw.");
        endFrame();
        return;
    }

    for (auto& entity : scene.entities())
    {
        auto* transform = entity->getComponent<TransformComponent>();
        auto* meshRenderer = entity->getComponent<MeshRendererComponent>();

        if (!transform || !meshRenderer) continue;

        auto& mesh = meshRenderer->mesh();
        auto& material = meshRenderer->material();
        auto& shader = material.shader();

        shader.bind();

        shader.setMat4("model", glm::value_ptr(transform->matrix()));
        shader.setMat4("view", glm::value_ptr(camera->viewMatrix()));
        shader.setMat4("projection", glm::value_ptr(camera->projectionMatrix()));

        if (auto* texture = material.texture())
        {
            texture->bind(0);
            shader.setInt("u_texture", 0);
        }

        RenderCommand::drawIndexed(mesh.vertexArray());
    }

    endFrame();
}

void Renderer::endFrame() {}

void Renderer::onResize(int width, int height)
{
    RenderCommand::setViewport(0, 0, width, height);
}
