#pragma once

#include "Core/Utility.h"
#include <memory>

namespace DarrJorge
{
class IWindow;
class Scene;
class Entity;
class IGUIPlatformBackend;
class IGUIRendererBackend;

enum class GizmoOperation
{
    Translate,
    Rotate,
    Scale
};

class EditorLayer final : public NonCopyable
{
public:
    explicit EditorLayer(IWindow& window);
    ~EditorLayer();

    void render(const Scene& scene);

    [[nodiscard]] bool wantsCaptureMouse() const;
    [[nodiscard]] bool wantsCaptureKeyboard() const;

private:
    std::unique_ptr<IGUIPlatformBackend> m_platformBackend;
    std::unique_ptr<IGUIRendererBackend> m_rendererBackend;

    Entity* m_selectedEntity{nullptr};

    GizmoOperation m_gizmoOperation{GizmoOperation::Translate};
};
}  // namespace DarrJorge
