#include "RenderCommand.h"
#include "RendererAPI.h"
#include "RendererAPIFactory.h"
#include "Log/Log.h"

using namespace DarrJorge;

DEFINE_LOG_CATEGORY_STATIC(LogRenderCommand);

std::unique_ptr<RendererAPI> RenderCommand::s_api;

void RenderCommand::init()
{
    if (s_api) return;

    s_api = RendererAPIFactory::Create();
    s_api->init();
}

void RenderCommand::drawIndexed(IVertexArray* vertexArray)
{
    if (!s_api)
    {
        LOG(LogRenderCommand, Error, "RenderCommand::drawIndexed called before init()");
        return;
    }
    s_api->drawIndexed(vertexArray);
}

void RenderCommand::setClearColor(const Math::Vec4& color)
{
    if (!s_api)
    {
        LOG(LogRenderCommand, Error, "RenderCommand::setClearColor called before init()");
        return;
    }
    s_api->setClearColor(color);
}

void RenderCommand::clear()
{
    if (!s_api)
    {
        LOG(LogRenderCommand, Error, "RenderCommand::clear called before init()");
        return;
    }
    s_api->clear();
}
