#include "RenderDeviceFactory.h"
#include "RenderDevice.h"

#if defined(ENGINE_RENDERER_OPENGL)
#include "Render/OpenGL/GLRenderDevice.h"
#endif

using namespace DarrJorge;

std::unique_ptr<RenderDevice> RenderDeviceFactory::Create()
{
#if defined(ENGINE_RENDERER_OPENGL)
    return std::make_unique<GLRenderDevice>();
#elif defined(ENGINE_RENDERER_D3D12)
#error "D3D12 renderer backend is not implemented yet"
#elif defined(ENGINE_RENDERER_VULKAN)
#error "Vulkan renderer backend is not implemented yet"
#else
#error "Unknown renderer backend"
#endif
}
