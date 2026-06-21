#include "WindowManagerFactory.h"
#include "GLFW/GLFWWindowManager.h"
#include "WinAPI/WinAPIWindowManager.h"

#include "WindowManager.h"

using namespace DarrJorge;

std::unique_ptr<WindowManager> WindowManagerFactory::Create()
{
#if defined(_WIN32)
#ifdef ENGINE_USE_GLFW
    return std::make_unique<GLFWWindowManager>();
#else
    return std::make_unique<WinAPIWindowManager>();
#endif

#elif defined(__linux__)
    return std::make_unique<GLFWWindowManager>();

#elif defined(__APPLE__)
    return std::make_unique<GLFWWindowManager>();
#else
#error "Unsupported platform"
#endif
}
