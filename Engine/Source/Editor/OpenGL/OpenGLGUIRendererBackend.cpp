#include "OpenGLGUIRendererBackend.h"

#include <imgui.h>
#include <imgui_impl_opengl3.h>

using namespace DarrJorge;

OpenGLGUIRendererBackend::OpenGLGUIRendererBackend()
{
    ImGui_ImplOpenGL3_Init("#version 330");
}

OpenGLGUIRendererBackend::~OpenGLGUIRendererBackend()
{
    ImGui_ImplOpenGL3_Shutdown();
}

void OpenGLGUIRendererBackend::newFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
}

void OpenGLGUIRendererBackend::renderDrawData()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
