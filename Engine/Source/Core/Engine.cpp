#include "Engine.h"
#include "Log/Log.h"

using namespace DarrJorge;

DEFINE_LOG_CATEGORY_STATIC(LogEngine)

Engine::Engine()
{
    LOG(LogEngine, Display, "Test Log #1 display");
    LOG(LogEngine, Error, "Test Log #2 display");
    LOG(LogEngine, Display, "Test Log #3 display");
}

Engine::~Engine() = default;

void Engine::run()
{
}
