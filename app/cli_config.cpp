// <!-- Machine Summary Block -->
// {"file":"app/cli_config.cpp","purpose":"Implements CLI argument parsing using CLI11 library for SimulationAutoTuner.","depends_on":["app/cli_config.h","CLI11"]}

#include "cli_config.h"
#include <CLI/CLI.hpp>

namespace sat {

CliConfig parseCli(int argc, char** argv) {
    CLI::App app{"SimulationAutoTuner - AI-based fluid simulation performance tuning"};

    CliConfig config;

    // Define command-line flags
    app.add_flag("-H,--headless", config.headless,
                 "Run in headless mode (no GUI rendering)");

    app.add_option("-s,--seed", config.seed,
                   "Random seed for deterministic simulation (default: 0)")
        ->check(CLI::NonNegativeNumber);

    app.add_option("-t,--target-ms", config.targetMs,
                   "Target frame time in milliseconds (default: 16.67 for 60 FPS)")
        ->check(CLI::PositiveNumber);

    app.add_option("-l,--log-level", config.logLevel,
                   "Logging level: trace, debug, info, warn, error, critical (default: info)")
        ->check(CLI::IsMember({"trace", "debug", "info", "warn", "error", "critical"}));

    // Parse arguments
    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError& e) {
        // Exit with proper code (0 for help, 1 for errors)
        std::exit(app.exit(e));
    }

    return config;
}

} // namespace sat
