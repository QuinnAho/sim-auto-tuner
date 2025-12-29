<!-- Machine Summary Block -->
{"file":"docs/ARCHITECTURE.md","purpose":"Documents the baseline repository directory layout for SimulationAutoTuner.","notes":["milestone_0_directory_structure"]}

# Repository Architecture Baseline

This document captures the canonical directory structure introduced in Milestone 0. Each directory has a single, explicit responsibility so that future milestones can evolve individual subsystems without coupling.

## Top-Level Directories

- `app/` - Contains application entry points (desktop UI shell, headless harness, sample tools). Targets depend on `sim/` and `render/`.
- `sim/` - Houses the core simulation engine modules migrated from `src/jet` plus new runtime tuning glue.
- `render/` - Rendering subsystem (viewport, frame capture, visualization helpers) that consumes simulation outputs.
- `bench/` - Benchmarks and performance regression tools kept separate from correctness tests.
- `tests/` - Unit/integration tests executed by CI; mirrors public APIs from `app/`, `sim/`, and `render/`.
- `docs/` - Project documentation (build guides, architecture notes, style guides).
- `third_party/` - Managed dependencies retrieved via vcpkg or vendored drop-in modules (fmt, spdlog, CLI11, etc.).
- `ai/` - Task automation framework (unchanged; do not overwrite manual context).
- `resources/` - Meshes/textures required by existing Jet samples; kept for compatibility.
- `src/` - Legacy Jet framework code. Migration will move relevant modules into the new `sim/` and `app/` trees without breaking history.
- `external/` - Legacy manual dependencies (cnpy, pybind11, etc.). Left intact to unblock legacy builds until vcpkg fully replaces them.

## Migration Notes

1. Net-new runtime features should target `app/`, `sim/`, or `render/` instead of `src/`.
2. Benchmarks and tests must not share build targets; CI consumes `tests/` while perf automation uses `bench/`.
3. Third-party code resides in `third_party/` (or vcpkg installed tree) to keep Git history for local patches.
4. Documentation must be placed within `docs/` and include Machine Summary Blocks per the AI Execution Contract.
5. `ai/` remains authoritative for workflow automation; tasks referencing directories above should link back to this file.

## Future Work Hooks

- `CMakeLists.txt` and `CMakePresets.json` will treat each directory as a standalone component library/executable to preserve SRP.
- Once `sim/` supersedes `src/jet`, the old tree can become a compatibility layer gated behind build options.
