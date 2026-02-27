#pragma once

#include <functional>
#include <string>

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

class IWindow
{
public:
    virtual ~IWindow() = default;

    virtual void setTitle(const std::string& title) = 0;
    virtual void setWindowForCurrentContext() = 0;

    virtual bool isValid() const = 0;
    virtual bool shouldClose() const = 0;

    virtual void swapBuffers() = 0;
};
}  // namespace DarrJorge

namespace std
{
template <> struct hash<DarrJorge::WindowId>
{
    size_t operator()(const DarrJorge::WindowId& id) const noexcept { return std::hash<unsigned int>{}(id.value); }
};
}  // namespace std