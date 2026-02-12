#include "Engine.h"
#include "Log/Log.h"

using namespace DarrJorge;

const LogCategory logName("LogEngine");

Engine::Engine()
{
    Log::getInstance().log(logName, LogVerbosity::Display, "Test Log display");
    Log::getInstance().log(logName, LogVerbosity::Warning, "Test Log warning");
    Log::getInstance().log(logName, LogVerbosity::Error, "Test Log error");
}

Engine::~Engine()
{
}

void Engine::run()
{
}
