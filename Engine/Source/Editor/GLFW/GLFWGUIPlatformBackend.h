#pragma once

#include "Editor/IGUIPlatformBackend.h"

namespace DarrJorge
{
class IWindow;

class GLFWGUIPlatformBackend final : public IGUIPlatformBackend
{
public:
    explicit GLFWGUIPlatformBackend(IWindow& window);
    ~GLFWGUIPlatformBackend() override;

    void newFrame() override;
};
}  // namespace DarrJorge
