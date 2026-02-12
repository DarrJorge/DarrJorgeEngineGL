#pragma once

namespace DarrJorge
{
class NonCopyable
{
protected:
    NonCopyable() = default;
    ~NonCopyable() = default;

    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;

    NonCopyable(const NonCopyable&&) = delete;
    NonCopyable& operator=(const NonCopyable&&) = delete;
};
}  // namespace DarrJorge

#if defined(_MSC_VER)
#define PLATFORM_BREAK() __debugbreak()
#elif defined(__clang__) || defined(__GNUC__)
#define PLATFORM_BREAK() __builtin_trap()
#else
#include <signal.h>
#define PLATFORM_BREAK() raise(SIGTRAP)
#endif
