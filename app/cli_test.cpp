// <!-- Machine Summary Block -->
// {"file":"app/cli_test.cpp","purpose":"Test program to validate CLI argument parsing functionality.","depends_on":["app/cli_config.h","sim/logging.h"]}

#include "cli_config.h"
#include "sim/logging.h"
#include <spdlog/spdlog.h>
#include <iostream>
#include <unordered_map>

namespace {

sat::logging::LogLevel ParseLogLevel(const std::string& levelStr) {
    static const std::unordered_map<std::string, sat::logging::LogLevel> kLevelMap = {
        {"trace", sat::logging::LogLevel::Trace},
        {"debug", sat::logging::LogLevel::Debug},
        {"info", sat::logging::LogLevel::Info},
        {"warn", sat::logging::LogLevel::Warn},
        {"error", sat::logging::LogLevel::Error},
        {"critical", sat::logging::LogLevel::Critical}
    };

    auto it = kLevelMap.find(levelStr);
    if (it != kLevelMap.end()) {
        return it->second;
    }
    return sat::logging::LogLevel::Info; // Default
}

} // anonymous namespace

int main(int argc, char** argv) {
    try {
        // Parse CLI arguments
        sat::CliConfig config = sat::parseCli(argc, argv);

        // Initialize logging
        sat::logging::InitializeLogging(ParseLogLevel(config.logLevel));

        // Display parsed configuration
        spdlog::info("=== CLI Configuration Test ===");
        spdlog::info("Headless mode: {}", config.headless ? "enabled" : "disabled");
        spdlog::info("Random seed: {}", config.seed);
        spdlog::info("Target frame time: {:.2f} ms ({:.1f} FPS)",
                     config.targetMs, 1000.0 / config.targetMs);
        spdlog::info("Log level: {}", config.logLevel);
        spdlog::info("=== CLI parsing successful ===");

        sat::logging::ShutdownLogging();
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
