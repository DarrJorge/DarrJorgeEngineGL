#pragma once

namespace DarrJorge
{
class Scene;

class Renderer final
{
public:
    Renderer();
    ~Renderer();

    void render(const Scene& scene);

private:
    void beginFrame();
    void endFrame();
};
}  // namespace DarrJorge