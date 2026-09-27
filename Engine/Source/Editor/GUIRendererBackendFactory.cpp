#include "GUIRendererBackendFactory.h"
#include "IGUIRendererBackend.h"

#if defined(ENGINE_RENDERER_OPENGL)
#include "Editor/OpenGL/OpenGLGUIRendererBackend.h"
#endif

using namespace DarrJorge;

std::unique_ptr<IGUIRendererBackend> GUIRendererBackendFactory::Create()
{
#if defined(ENGINE_RENDERER_OPENGL)
    return std::make_unique<OpenGLGUIRendererBackend>();
#elif defined(ENGINE_RENDERER_D3D12)
#error "D3D12 ImGui renderer backend is not implemented yet"
#elif defined(ENGINE_RENDERER_VULKAN)
#error "Vulkan ImGui renderer backend is not implemented yet"
#else
#error "Unknown renderer backend"
#endif
}
