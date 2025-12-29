// <!-- Machine Summary Block -->
// {"file":"sim/include/sim/logging.h","purpose":"Declares SimulationAutoTuner logging utilities backed by spdlog/fmt."}
#pragma once

#include <string_view>

namespace sat::logging {

enum class LogLevel {
    Trace,
    Debug,
    Info,
    Warn,
    Error,
    Critical
};

void InitializeLogging(LogLevel level = LogLevel::Info);

void ShutdownLogging();

void SetLogLevel(LogLevel level);

std::string_view ToString(LogLevel level);

}  // namespace sat::logging
