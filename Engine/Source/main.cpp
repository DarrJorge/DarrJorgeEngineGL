#include "Core/Engine.h"
#include <memory>
#include "Window/WindowManagerFactory.h"
#include "Window/WindowManager.h"

using namespace DarrJorge;

int main()
{
    auto windowManager = WindowManagerFactory::Create();
    Engine engine(std::move(windowManager));
    engine.run();

    return EXIT_SUCCESS;
}