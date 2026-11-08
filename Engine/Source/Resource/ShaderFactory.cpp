#include "ShaderFactory.h"
#include "Core/FileUtils.h"
#include "Core/LRUCache.h"
#include "Render/RHI/IShader.h"
#include "Render/RHI/RenderDevice.h"
#include "Render/RHI/RenderDeviceFactory.h"

using namespace DarrJorge;

namespace
{
constexpr size_t c_maxCachedShaders = 32;
}

std::shared_ptr<IShader> ShaderFactory::createShader(const std::string& vertexPath, const std::string& fragmentPath)
{
    static LRUCache<std::string, std::shared_ptr<IShader>> s_cache(c_maxCachedShaders);

    const std::string key = vertexPath + "|" + fragmentPath;
    if (auto cached = s_cache.get(key))
    {
        return cached->get();
    }

    const std::string vertexSource = FileUtils::readTextFile(vertexPath);
    const std::string fragmentSource = FileUtils::readTextFile(fragmentPath);

    auto renderDevice = RenderDeviceFactory::Create();
    auto shader = renderDevice->createShaderProgram(vertexSource, fragmentSource);

    s_cache.put(key, shader);

    return shader;
}
