#pragma once

#include <memory>

namespace DarrJorge
{
class WindowManager;

class WindowManagerFactory
{
public:
    static std::unique_ptr<WindowManager> Create();
};
}  // namespace DarrJorge