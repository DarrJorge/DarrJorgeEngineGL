#include "Log.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

#include <filesystem>
#include <chrono>
#include <unordered_map>

using namespace DarrJorge;
namespace fs = std::filesystem;

namespace
{
const std::unordered_map<LogVerbosity, spdlog::level::level_enum> c_verbosityMap = {
    {LogVerbosity::NoLogging, spdlog::level::off}, {LogVerbosity::Display, spdlog::level::info},
    {LogVerbosity::Warning, spdlog::level::warn},  {LogVerbosity::Error, spdlog::level::err},
    {LogVerbosity::Log, spdlog::level::info},      {LogVerbosity::Fatal, spdlog::level::critical}};

constexpr const char* c_logPattern = "[%H:%M:%S.%e] [%^%l%$] %v";
const fs::path c_logDirectory = "logs";
constexpr const char* c_logFilePrefix = "Log";
constexpr const char* c_logFileExtension = "txt";
constexpr const char* c_timestampFormat = "{:%Y.%d.%m-%H.%M.%S}";
}  // namespace

// pImpl
class Log::Impl
{
public:
    Impl()
    {
        auto consoleLink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        m_consoleLogger = std::make_unique<spdlog::logger>("console", consoleLink);
        m_consoleLogger->set_pattern(c_logPattern);

        auto fileLink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(makeLogFile().string());
        m_fileLogger = std::make_unique<spdlog::logger>("file", fileLink);
        m_fileLogger->set_pattern(c_logPattern);
    }
    void log(LogVerbosity verbosity, const std::string& message)
    {
        const auto spdLevel = c_verbosityMap.at(verbosity);

        if (verbosity != LogVerbosity::Log && m_consoleLogger->should_log(spdLevel))
        {
            m_consoleLogger->log(spdLevel, message);
        }

        if (m_fileLogger->should_log(spdLevel))
        {
            m_fileLogger->log(spdLevel, message);
        }

        if (verbosity == LogVerbosity::Fatal)
        {
            // TODO implement Platform_Break
        }
    }

private:
    std::unique_ptr<spdlog::logger> m_consoleLogger;
    std::unique_ptr<spdlog::logger> m_fileLogger;

    fs::path makeLogFile() const
    {
        fs::create_directory(c_logDirectory);
        const auto now = std::chrono::system_clock::now();
        const auto nowSeconds = std::chrono::floor<std::chrono::seconds>(now);
        const auto timestamp = std::format(c_timestampFormat, nowSeconds);
        const auto filename = std::format("{}-{}.{}", c_logFilePrefix, c_logPattern, c_logFileExtension);
        return c_logDirectory / filename;
    }
};

// interface
Log::Log() : m_impl(std::make_unique<Impl>()) {}
Log::~Log() = default;

void Log::log(const LogCategory& category, LogVerbosity verbosity, const std::string& message, bool showLocation,
              const std::source_location location)
{
    const std::string formatMsg = showLocation
                                      ? std::format("[{}] [{}:{}] {}", category.name(), location.function_name(), location.line(), message)
                                      : std::format("[{}] {}", category.name(), message);

    m_impl->log(verbosity,formatMsg);
}