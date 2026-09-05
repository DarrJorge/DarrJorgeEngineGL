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
    void onResize(int width, int height);

private:
    void beginFrame();
    void endFrame();
};
}  // namespace DarrJorge