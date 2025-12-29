# Task Checklist: TASK_001_milestone_0_baseline

## Task: Milestone 0 — Repo + Tooling Baseline

### Pre-execution
- [x] Read task.json and understand acceptance criteria
- [x] Read current CMakeLists.txt to understand existing build system
- [x] Verify existing directory structure (src/, external/, etc.)
- [x] Confirm ai/ directory exists and won't be overwritten

### Phase 1: Directory Structure
- [x] Create app/ directory for application entry points
- [x] Create sim/ directory for simulation engine code (will migrate from src/)
- [x] Create render/ directory for rendering subsystem
- [x] Create bench/ directory for benchmarking code
- [x] Create tests/ directory for unit and integration tests
- [x] Create docs/ directory for documentation
- [x] Create third_party/ directory for modern dependency management
- [x] Document directory structure decisions in docs/ARCHITECTURE.md

### Phase 2: vcpkg Integration
- [x] Create vcpkg.json manifest file
- [x] Add spdlog dependency to vcpkg.json
- [x] Add fmt dependency to vcpkg.json
- [x] Add CLI11 dependency to vcpkg.json
- [x] Test vcpkg dependency resolution

### Phase 3: CMake Modernization
- [x] Create CMakePresets.json with Debug preset
- [x] Add Release preset to CMakePresets.json
- [x] Refactor root CMakeLists.txt to use modern CMake (3.15+)
- [x] Integrate vcpkg toolchain file in CMakePresets.json
- [x] Create app/CMakeLists.txt for application targets
- [x] Create sim/CMakeLists.txt for simulation library
- [x] Create tests/CMakeLists.txt for test targets
- [x] Create bench/CMakeLists.txt for benchmark targets
- [x] Verify existing src/ builds still work
- [x] Test one-command build: cmake --preset Release && cmake --build --preset Release

### Phase 4: Code Quality Tooling
- [x] Create .clang-format file with project style rules
- [x] Create .clang-tidy file with linting rules
- [x] Test clang-format on a sample file
- [x] Test clang-tidy on a sample file
- [x] Document code style in docs/CODING_STYLE.md

### Phase 5: Logging Infrastructure
- [x] Create sim/logging.h header for logging utilities
- [x] Create sim/logging.cpp implementation
- [x] Integrate spdlog in logging implementation
- [x] Integrate fmt for formatting
- [x] Create simple test program in app/ that logs a message
- [x] Build and run test program to verify logging works
- [x] Add logging initialization to main application entry point

### Phase 6: CLI Argument Parsing
- [x] Create app/cli_config.h header for CLI configuration
- [x] Create app/cli_config.cpp implementation using CLI11
- [x] Add --headless flag parsing
- [x] Add --seed flag parsing (integer)
- [x] Add --target-ms flag parsing (float/double)
- [x] Create test program that prints parsed CLI arguments
- [x] Build and run test with various flag combinations
- [x] Document CLI flags in docs/CLI_REFERENCE.md

### Phase 7: GitHub Actions CI
- [x] Create .github/workflows/ directory
- [x] Create ci.yml workflow file
- [x] Add Windows build job (MSVC)
- [x] Add Linux build job (GCC)
- [x] Configure vcpkg caching in CI
- [x] Configure build artifact upload
- [x] Add build matrix for Debug/Release on both platforms
- [x] Test CI workflow (push to trigger)
- [x] Verify CI passes on Windows
- [x] Verify CI passes on Linux
- [x] Add CI status badge to README.md

### Phase 8: Documentation
- [x] Update README.md with new build instructions
- [x] Create docs/BUILD.md with detailed build guide
- [x] Document vcpkg setup in docs/BUILD.md
- [x] Document CMake presets usage
- [x] Create docs/DEPENDENCIES.md listing all third-party libraries
- [x] Add Machine Summary Blocks to all new files created

### Validation
- [ ] Code compiles without warnings on Windows (MSVC)
- [ ] Code compiles without warnings on Linux (GCC)
- [ ] No unused abstractions introduced
- [ ] Public interfaces are minimal and justified
- [ ] No per-frame dynamic allocations in hot paths (N/A for tooling)
- [ ] Ownership and lifetimes are explicit
- [ ] clang-format runs successfully on all new code
- [ ] clang-tidy passes without critical warnings
- [ ] Single command build works: cmake --preset Release && cmake --build --preset Release
- [ ] CLI parsing test works with all three flags
- [ ] Logging test outputs visible log messages
- [ ] GitHub Actions CI is green on both platforms
- [ ] All acceptance criteria from task.json are met

### Completion
- [ ] All steps marked complete
- [ ] progress.ndjson contains task_completed event
- [ ] No validation rules violated
- [ ] All new files have Machine Summary Blocks

---

**Notes:**
- Mark steps with `[x]` only after validation succeeds
- Never mark multiple steps at once
- Log each step completion to progress.ndjson
- Preserve existing Jet framework code in src/ - integration comes later
- The ai/ directory already exists - do not overwrite
- Stop and log blocker if vcpkg installation issues arise
