#include "GUIPlatformBackendFactory.h"
#include "IGUIPlatformBackend.h"

#if defined(_WIN32)
#ifdef ENGINE_USE_GLFW
#include "Editor/GLFW/GLFWImGuiPlatformBackend.h"
#endif
#elif defined(__linux__)
#include "Editor/GLFW/GLFWImGuiPlatformBackend.h"
#elif defined(__APPLE__)
#include "Editor/GLFW/GLFWGUIPlatformBackend.h"
#endif

using namespace DarrJorge;

std::unique_ptr<IGUIPlatformBackend> GUIPlatformBackendFactory::Create(IWindow& window)
{
#if defined(_WIN32)
#ifdef ENGINE_USE_GLFW
    return std::make_unique<GLFWGUIPlatformBackend>(window);
#else
#error "No ImGui platform backend available for the WinAPI window backend yet"
#endif
#elif defined(__linux__)
    return std::make_unique<GLFWImGuiPlatformBackend>(window);
#elif defined(__APPLE__)
    return std::make_unique<GLFWGUIPlatformBackend>(window);
#else
#error "Unsupported platform"
#endif
}
