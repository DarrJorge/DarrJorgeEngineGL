#pragma once

#include <memory>

namespace DarrJorge
{
class RendererAPI;

class RendererAPIFactory
{
public:
    static std::unique_ptr<RendererAPI> Create();
};
}  // namespace DarrJorge
