// <!-- Machine Summary Block -->
// {"file":"app/main.cpp","purpose":"Sample SimulationAutoTuner entry point that exercises the logging subsystem."}

#include "sim/logging.h"

#include <spdlog/spdlog.h>

int main() {
    sat::logging::InitializeLogging(sat::logging::LogLevel::Debug);
    spdlog::info("SimulationAutoTuner logging pipeline initialized.");
    spdlog::debug("This is a debug message used to confirm log-level filtering.");
    sat::logging::ShutdownLogging();
    return 0;
}
