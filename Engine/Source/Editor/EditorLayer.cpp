#include "EditorLayer.h"
#include "IGUIPlatformBackend.h"
#include "IGUIRendererBackend.h"
#include "GUIPlatformBackendFactory.h"
#include "GUIRendererBackendFactory.h"
#include "Scene/Scene.h"
#include "Scene/Entity.h"
#include "Scene/Components/Component.h"
#include "Scene/Components/TransformComponent.h"
#include "Log/Log.h"

#include <imgui.h>
#include <glm/glm.hpp>
#include <cstdlib>

using namespace DarrJorge;

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
