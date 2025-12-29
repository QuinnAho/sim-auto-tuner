// <!-- Machine Summary Block -->
// {"file":"app/cli_config.h","purpose":"Defines CLI configuration structure and parsing interface for SimulationAutoTuner application.","exports":["CliConfig","parseCli"],"depends_on":["CLI11"],"notes":["Uses CLI11 for argument parsing"]}

#pragma once

#include <string>

namespace sat {

/// Configuration structure populated from command-line arguments
struct CliConfig {
    bool headless = false;       ///< Run without GUI (headless mode)
    int seed = 0;                ///< Random seed for deterministic simulation
    double targetMs = 16.67;     ///< Target frame time in milliseconds (default: 60 FPS)
    std::string logLevel = "info"; ///< Logging level (trace/debug/info/warn/error/critical)
};

/// Parse command-line arguments into CliConfig
/// @param argc Argument count from main()
/// @param argv Argument values from main()
/// @return Parsed configuration structure
/// @throws CLI::ParseError if parsing fails
CliConfig parseCli(int argc, char** argv);

} // namespace sat
