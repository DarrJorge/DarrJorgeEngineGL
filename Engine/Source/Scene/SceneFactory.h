#pragma once

#include <memory>

namespace DarrJorge
{
class Scene;

class SceneFactory
{
public:
    static std::unique_ptr<Scene> createDemoScene();
};
}  // namespace DarrJorge
