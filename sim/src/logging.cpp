// <!-- Machine Summary Block -->
// {"file":"sim/src/logging.cpp","purpose":"Implements SimulationAutoTuner logging utilities using spdlog/fmt."}

#include "sim/logging.h"

#include <array>
#include <atomic>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace sat::logging {
namespace {

std::atomic<bool> g_initialized{false};

spdlog::level::level_enum ToSpdlogLevel(LogLevel level) {
    switch (level) {
        case LogLevel::Trace:
            return spdlog::level::trace;
        case LogLevel::Debug:
            return spdlog::level::debug;
        case LogLevel::Info:
            return spdlog::level::info;
        case LogLevel::Warn:
            return spdlog::level::warn;
        case LogLevel::Error:
            return spdlog::level::err;
        case LogLevel::Critical:
            return spdlog::level::critical;
        default:
            return spdlog::level::info;
    }
}

}  // namespace

void InitializeLogging(LogLevel level) {
    if (g_initialized.exchange(true)) {
        SetLogLevel(level);
        return;
    }

    auto logger = spdlog::stdout_color_mt("sat");
    logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
    spdlog::set_default_logger(logger);
    SetLogLevel(level);
    spdlog::info("Logging initialized at {} level", ToString(level));
}

void ShutdownLogging() {
    if (!g_initialized.exchange(false)) {
        return;
    }
    spdlog::info("Shutting down logging.");
    spdlog::shutdown();
}

void SetLogLevel(LogLevel level) {
    spdlog::set_level(ToSpdlogLevel(level));
}

std::string_view ToString(LogLevel level) {
    static constexpr std::array<std::string_view, 6> kNames = {
        "Trace", "Debug", "Info", "Warn", "Error", "Critical"};
    const auto index = static_cast<size_t>(level);
    if (index < kNames.size()) {
        return kNames[index];
    }
    return "Unknown";
}

}  // namespace sat::logging
