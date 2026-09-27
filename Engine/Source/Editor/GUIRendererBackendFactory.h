#pragma once

#include <memory>

namespace DarrJorge
{
class IGUIRendererBackend;

class GUIRendererBackendFactory
{
public:
    static std::unique_ptr<IGUIRendererBackend> Create();
};
}  // namespace DarrJorge
