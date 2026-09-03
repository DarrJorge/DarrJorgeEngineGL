#include "RendererAPIFactory.h"
#include "RendererAPI.h"

#if defined(ENGINE_RENDERER_OPENGL)
#include "Render/OpenGL/GLRendererAPI.h"
#endif

using namespace DarrJorge;

std::unique_ptr<RendererAPI> RendererAPIFactory::Create()
{
#if defined(ENGINE_RENDERER_OPENGL)
    return std::make_unique<GLRendererAPI>();
#elif defined(ENGINE_RENDERER_D3D12)
#error "D3D12 renderer backend is not implemented yet"
#elif defined(ENGINE_RENDERER_VULKAN)
#error "Vulkan renderer backend is not implemented yet"
#else
#error "Unknown renderer backend"
#endif
}
