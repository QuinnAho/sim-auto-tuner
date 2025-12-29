// <!-- Machine Summary Block -->
// {"file":"app/include/app/cli_config.h","purpose":"Defines CLI configuration structures and parsing for SimulationAutoTuner."}
#pragma once

#include <cstdint>

namespace sat::app {

struct CliConfig {
    bool headless = false;
    std::uint32_t seed = 0;
    double target_ms = 16.0;
};

CliConfig ParseCli(int argc, char** argv);

}  // namespace sat::app
