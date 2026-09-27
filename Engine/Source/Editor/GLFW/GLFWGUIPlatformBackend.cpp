#include "GLFWGUIPlatformBackend.h"
#include "Window/IWindow.h"

#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>

using namespace DarrJorge;

GLFWGUIPlatformBackend::GLFWGUIPlatformBackend(IWindow& window)
{
    auto* glfwWindow = static_cast<GLFWwindow*>(window.nativeHandle());
    ImGui_ImplGlfw_InitForOpenGL(glfwWindow, /*install_callbacks=*/true);
}

GLFWGUIPlatformBackend::~GLFWGUIPlatformBackend()
{
    ImGui_ImplGlfw_Shutdown();
}

void GLFWGUIPlatformBackend::newFrame()
{
    ImGui_ImplGlfw_NewFrame();
}
