<!-- Machine Summary Block -->
{"file":"docs/CLI_REFERENCE.md","purpose":"Documents all command-line interface flags and options for SimulationAutoTuner.","depends_on":["app/cli_config.h"]}

# CLI Reference — SimulationAutoTuner

This document describes all command-line options available for the SimulationAutoTuner application.

## Usage

```bash
sat_app [OPTIONS]
```

## Options

### `-h, --help`
Print help message and exit.

**Example:**
```bash
sat_app --help
```

---

### `-H, --headless`
Run in headless mode (no GUI rendering).

**Type:** Boolean flag
**Default:** `false` (GUI mode enabled)

**Use case:** Running simulations on servers or in CI environments without display output.

**Example:**
```bash
sat_app --headless
```

---

### `-s, --seed <INTEGER>`
Random seed for deterministic simulation.

**Type:** Non-negative integer
**Default:** `0`

**Use case:** Reproducible simulation runs for debugging, benchmarking, or testing. Using the same seed will produce identical simulation results.

**Example:**
```bash
sat_app --seed 42
```

---

### `-t, --target-ms <FLOAT>`
Target frame time in milliseconds.

**Type:** Positive floating-point number
**Default:** `16.67` (equivalent to 60 FPS)

**Use case:** Setting performance targets for the AI tuning system. The value represents the desired time budget per simulation frame.

**Common values:**
- `16.67` ms → 60 FPS
- `33.33` ms → 30 FPS
- `8.33` ms → 120 FPS

**Example:**
```bash
sat_app --target-ms 33.33
```

---

### `-l, --log-level <LEVEL>`
Logging verbosity level.

**Type:** String (enum)
**Default:** `info`
**Allowed values:** `trace`, `debug`, `info`, `warn`, `error`, `critical`

**Level descriptions:**
- `trace` — Most verbose; includes all debug information and internal state
- `debug` — Detailed diagnostic information useful for development
- `info` — General informational messages about application progress
- `warn` — Warning messages for potentially problematic situations
- `error` — Error messages for failures that don't stop execution
- `critical` — Critical errors that may cause application termination

**Example:**
```bash
sat_app --log-level debug
```

---

## Combined Usage Examples

### Headless benchmark with specific seed and target
```bash
sat_app --headless --seed 12345 --target-ms 16.67 --log-level info
```

### Debug run with verbose logging
```bash
sat_app --seed 999 --log-level trace
```

### Production run targeting 30 FPS
```bash
sat_app --headless --target-ms 33.33 --log-level warn
```

---

## Implementation Notes

- CLI parsing is implemented using [CLI11](https://github.com/CLIUtils/CLI11) library
- All flags can be specified in short (`-H`) or long (`--headless`) form
- Invalid values will produce descriptive error messages
- The `--help` flag takes precedence and will display help without running the simulation
- Configuration structure is defined in `app/cli_config.h`

---

**Last updated:** 2025-12-29
**CLI version:** 1.0
