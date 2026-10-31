#include "EditorLayer.h"
#include "IGUIPlatformBackend.h"
#include "IGUIRendererBackend.h"
#include "GUIPlatformBackendFactory.h"
#include "GUIRendererBackendFactory.h"
#include "Scene/Scene.h"
#include "Scene/Entity.h"
#include "Scene/Components/Component.h"
#include "Scene/Components/TransformComponent.h"
#include "Scene/Components/CameraComponent.h"
#include "Log/Log.h"

#include <imgui.h>
#include <ImGuizmo.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>

using namespace DarrJorge;

namespace
{
ImGuizmo::OPERATION ToImGuizmoOperation(GizmoOperation operation)
{
    switch (operation)
    {
        case GizmoOperation::Translate: return ImGuizmo::TRANSLATE;
        case GizmoOperation::Rotate: return ImGuizmo::ROTATE;
        case GizmoOperation::Scale: return ImGuizmo::SCALE;
    }
    return ImGuizmo::TRANSLATE;
}
}

EditorLayer::EditorLayer(IWindow& window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    m_platformBackend = GUIPlatformBackendFactory::Create(window);
    m_rendererBackend = GUIRendererBackendFactory::Create();
}

EditorLayer::~EditorLayer()
{
    m_rendererBackend.reset();
    m_platformBackend.reset();
    ImGui::DestroyContext();
}

void EditorLayer::render(const Scene& scene)
{
    m_rendererBackend->newFrame();
    m_platformBackend->newFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit"))
            {
                std::exit(EXIT_SUCCESS);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    if (ImGui::Begin("Scene"))
    {
        for (const auto& entity : scene.entities())
        {
            const bool isSelected = (entity.get() == m_selectedEntity);
            if (ImGui::Selectable(entity->name().c_str(), isSelected))
            {
                m_selectedEntity = entity.get();
            }
        }
    }
    ImGui::End();

    if (ImGui::Begin("Inspector"))
    {
        if (m_selectedEntity)
        {
            ImGui::Text("Name: %s", m_selectedEntity->name().c_str());
            ImGui::Separator();

            if (ImGui::RadioButton("Translate", m_gizmoOperation == GizmoOperation::Translate))
            {
                m_gizmoOperation = GizmoOperation::Translate;
            }
            ImGui::SameLine();
            if (ImGui::RadioButton("Rotate", m_gizmoOperation == GizmoOperation::Rotate))
            {
                m_gizmoOperation = GizmoOperation::Rotate;
            }
            ImGui::SameLine();
            if (ImGui::RadioButton("Scale", m_gizmoOperation == GizmoOperation::Scale))
            {
                m_gizmoOperation = GizmoOperation::Scale;
            }
            ImGui::Separator();

            for (auto* component : m_selectedEntity->components())
            {
                const auto typeName = component->typeName();
                ImGui::TextUnformatted(typeName.data(), typeName.data() + typeName.size());

                if (component->typeId() == ComponentTypeIdGenerator::get<TransformComponent>())
                {
                    auto* transform = static_cast<TransformComponent*>(component);

                    glm::vec3 position = transform->position();
                    if (ImGui::DragFloat3("Position", &position.x, 0.1f))
                    {
                        transform->setPosition(position);
                    }

                    glm::vec3 rotationDegrees = glm::degrees(transform->rotationEuler());
                    if (ImGui::DragFloat3("Rotation", &rotationDegrees.x, 1.0f))
                    {
                        transform->setRotationEuler(glm::radians(rotationDegrees));
                    }

                    glm::vec3 scale = transform->scale();
                    if (ImGui::DragFloat3("Scale", &scale.x, 0.1f))
                    {
                        transform->setScale(scale);
                    }
                }

                ImGui::Separator();
            }
        }
        else
        {
            ImGui::TextDisabled("No entity selected");
        }
    }
    ImGui::End();

    if (ImGui::Begin("Console"))
    {
        for (const auto& line : Log::getInstance().history())
        {
            ImGui::TextUnformatted(line.c_str());
        }
        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        {
            ImGui::SetScrollHereY(1.0f);
        }
    }
    ImGui::End();

    if (m_selectedEntity)
    {
        if (auto* transform = m_selectedEntity->getComponent<TransformComponent>())
        {
            if (const CameraComponent* camera = scene.activeCamera())
            {
                const ImGuiIO& io = ImGui::GetIO();
                ImGuizmo::SetOrthographic(false);
                ImGuizmo::SetDrawlist(ImGui::GetBackgroundDrawList());
                ImGuizmo::SetRect(0.0f, 0.0f, io.DisplaySize.x, io.DisplaySize.y);

                glm::mat4 matrix = transform->matrix();
                if (ImGuizmo::Manipulate(glm::value_ptr(camera->viewMatrix()), glm::value_ptr(camera->projectionMatrix()),
                        ToImGuizmoOperation(m_gizmoOperation), ImGuizmo::LOCAL, glm::value_ptr(matrix)))
                {
                    float translation[3];
                    float rotationDegrees[3];
                    float scale[3];
                    ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(matrix), translation, rotationDegrees, scale);

                    switch (m_gizmoOperation)
                    {
                        case GizmoOperation::Translate:
                            transform->setPosition({translation[0], translation[1], translation[2]});
                            break;
                        case GizmoOperation::Rotate:
                            transform->setRotationEuler(glm::radians(glm::vec3{rotationDegrees[0], rotationDegrees[1], rotationDegrees[2]}));
                            break;
                        case GizmoOperation::Scale:
                            transform->setScale({scale[0], scale[1], scale[2]});
                            break;
                    }
                }
            }
        }
    }

    ImGui::Render();
    m_rendererBackend->renderDrawData();
}

bool EditorLayer::wantsCaptureMouse() const
{
    return ImGui::GetIO().WantCaptureMouse;
}

bool EditorLayer::wantsCaptureKeyboard() const
{
    return ImGui::GetIO().WantCaptureKeyboard;
}
