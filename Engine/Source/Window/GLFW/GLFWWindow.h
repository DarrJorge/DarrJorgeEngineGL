#pragma once

#include <functional>
#include <string>

class GLFWwindow;

namespace DarrJorge
{
struct WindowId
{
    unsigned int value{0};
    constexpr explicit WindowId(unsigned int id) : value(id) {}

    constexpr WindowId operator++(int)
    {
        WindowId temp = *this;
        ++value;
        return temp;
    }

    constexpr auto operator<=>(const WindowId&) const = default;
};

struct WindowSettings
{
    std::string title{};
    int width{1280};
    int height{720};
    int x{100};
    int y{100};
};

class GLFWWindow final
{
public:
    GLFWWindow(const WindowSettings& settings);
    ~GLFWWindow();

    void setTitle(const std::string& title);
    void setWindowForCurrentContext();

    bool isValid() const;
    bool shouldClose() const;

    void swapBuffers();

private:
    GLFWwindow* m_window{nullptr};
};
}  // namespace DarrJorge

namespace std
{
template <> struct hash<DarrJorge::WindowId>
{
    size_t operator()(const DarrJorge::WindowId& id) const noexcept { return std::hash<unsigned int>{}(id.value); }
};
}  // namespace std