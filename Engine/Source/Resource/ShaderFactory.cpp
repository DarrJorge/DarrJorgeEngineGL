#include "ShaderFactory.h"
#include "Core/FileUtils.h"
#include "Render/RHI/RenderDevice.h"
#include "Render/RHI/RenderDeviceFactory.h"

using namespace DarrJorge;

std::shared_ptr<IShader> ShaderFactory::createShader(const std::string& vertexPath, const std::string& fragmentPath)
{
    const std::string vertexSource = FileUtils::readTextFile(vertexPath);
    const std::string fragmentSource = FileUtils::readTextFile(fragmentPath);

    auto renderDevice = RenderDeviceFactory::Create();
    return renderDevice->createShaderProgram(vertexSource, fragmentSource);
}
