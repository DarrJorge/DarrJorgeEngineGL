#include "RenderCommand.h"
#include "Render/OpenGL/GLRendererAPI.h"

using namespace DarrJorge;

RendererAPI* RenderCommand::s_api = new GLRendererAPI;
