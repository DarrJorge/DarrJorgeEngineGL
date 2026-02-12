#pragma once

#include <cstdint>
#include <string>
#include <source_location>
#include <concepts>
#include <memory>
#include <format>
#include "Core/Utility.h"

namespace DarrJorge
{
enum class LogVerbosity : uint8_t
{
    NoLogging = 0,
    Display,
    Warning,
    Error,
    Log,
    Fatal
};

struct LogCategory
{
    explicit LogCategory(const std::string& name) : m_name(name) {}
    std::string name() const { return m_name; }

private:
    const std::string m_name;
};

class Log final : public NonCopyable
{
public:
    static Log& getInstance()
    {
        static Log instance;
        return instance;
    }

    void log(const LogCategory& category, LogVerbosity verbosity, const std::string& message, bool showLocation = false,
             const std::source_location location = std::source_location::current());

private:
    Log();
    ~Log();

    class Impl;
    std::unique_ptr<Impl> m_impl;
};
}  // namespace DarrJorge