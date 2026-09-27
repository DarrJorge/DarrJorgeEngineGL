#pragma once

#include "Editor/IGUIRendererBackend.h"

namespace DarrJorge
{
class OpenGLGUIRendererBackend final : public IGUIRendererBackend
{
public:
    OpenGLGUIRendererBackend();
    ~OpenGLGUIRendererBackend() override;

    void newFrame() override;
    void renderDrawData() override;
};
}  // namespace DarrJorge
