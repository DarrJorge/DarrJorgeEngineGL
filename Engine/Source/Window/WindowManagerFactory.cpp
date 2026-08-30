#include "WindowManagerFactory.h"
#include "WindowManager.h"

#if defined(_WIN32)
#ifdef ENGINE_USE_GLFW
#include "GLFW/GLFWWindowManager.h"
#else
#include "WinAPI/WinAPIWindowManager.h"
#endif
#elif defined(__linux__)
#include "GLFW/GLFWWindowManager.h"
#elif defined(__APPLE__)
#include "GLFW/GLFWWindowManager.h"
#endif

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
