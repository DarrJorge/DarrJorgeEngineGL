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
};
}  // namespace DarrJorge
