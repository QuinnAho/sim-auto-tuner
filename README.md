# SimulationAutoTuner

[![CI](https://github.com/QuinnAho/sim-auto-tuner/actions/workflows/ci.yml/badge.svg)](https://github.com/QuinnAho/sim-auto-tuner/actions/workflows/ci.yml) [![License](http://img.shields.io/:license-mit-blue.svg)](LICENSE.md)

**SimulationAutoTuner** is a modern C++ fluid simulation engine with AI-assisted runtime performance tuning. Built on the foundation of [Fluid Engine Dev (Jet)](https://github.com/doyubkim/fluid-engine-dev) by Doyub Kim, this project extends the framework with:

- **AI-based parameter optimization** for real-time performance tuning
- **Modern C++17 codebase** with CMake 3.23+ and vcpkg dependency management
- **Cross-platform CI/CD** with GitHub Actions (Windows, Linux)
- **Production-ready tooling**: clang-format, clang-tidy, spdlog, CLI11

## Project Status

**Active Development** - Currently implementing Milestone 0 (tooling baseline) and Milestone 1 (UI shell).

The legacy Jet simulation code is temporarily disabled while the new SimulationAutoTuner architecture is being established.

## Key Features
* Basic math and geometry operations and data structures
* Spatial query accelerators
* SPH and PCISPH fluid simulators
* Stable fluids-based smoke simulator
* Level set-based liquid simulator
* PIC, FLIP, and APIC fluid simulators
* Upwind, ENO, and FMM level set solvers
* Jacobi, Gauss-Seidel, SOR, MG, CG, ICCG, and MGPCG linear system solvers
* Spherical, SPH, Zhu & Bridson, and Anisotropic kernel for points-to-surface converter
* Converters between signed distance function and triangular mesh
* C++ and Python API
* Intel TBB, OpenMP, and C++11 multi-threading backends

Every simulator has both 2-D and 3-D implementations.

## Quick Start

### Prerequisites

- **CMake 3.23+**
- **C++17 compiler**: MSVC 2022, GCC 9+, or Clang 10+
- **Ninja build system** (installed automatically on most systems)
- **Git** (with submodules support)

### Clone the Repository

```bash
git clone https://github.com/QuinnAho/sim-auto-tuner.git --recursive
cd sim-auto-tuner
```

### Build (One-Command)

SimulationAutoTuner uses CMake Presets for easy, reproducible builds:

```bash
# Configure and build Release
cmake --preset Release
cmake --build --preset Release

# Or for Debug
cmake --preset Debug
cmake --build --preset Debug
```

**Note**: vcpkg dependencies (spdlog, fmt, CLI11) are automatically downloaded and built on first configure.

### Run Tests

```bash
# Run CLI test
./build/Release/bin/sat_cli_test --help
./build/Release/bin/sat_cli_test --headless --seed 42 --target-ms 16.67
```

### Command-Line Options

SimulationAutoTuner supports the following flags:

- `--headless` - Run without GUI (headless mode)
- `--seed <N>` - Random seed for deterministic simulation
- `--target-ms <N>` - Target frame time in milliseconds (default: 16.67 for 60 FPS)
- `--log-level <level>` - Logging verbosity: trace, debug, info, warn, error, critical

See [docs/CLI_REFERENCE.md](docs/CLI_REFERENCE.md) for full documentation.

### More Information

- **Detailed Build Guide**: [docs/BUILD.md](docs/BUILD.md) (coming soon)
- **Architecture Overview**: [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md)
- **Code Style Guide**: [docs/CODING_STYLE.md](docs/CODING_STYLE.md)
- **Dependencies**: [docs/DEPENDENCIES.md](docs/DEPENDENCIES.md) (coming soon)

## Documentations

All the documentations for the framework can be found from [the project website](http://fluidenginedevelopment.org/documentation/) including the API reference.

## Examples

Here are some of the example simulations generated using Jet framework. Corresponding example codes can be found under src/examples. All images are rendered using [Mitsuba renderer](https://www.mitsuba-renderer.org/) and the Mitsuba scene files can be found from [the demo repository](https://github.com/doyubkim/fluid-engine-dev-demo/). Find out more demos from [the project website](http://fluidenginedevelopment.org/examples/).

### FLIP Simulation Example

![FLIP Example](https://github.com/doyubkim/fluid-engine-dev/raw/main/doc/img/flip_dam_breaking.png "FLIP Example")

### PIC Simulation Example

![PIC Example](https://github.com/doyubkim/fluid-engine-dev/raw/main/doc/img/pic_dam_breaking.png "PIC Example")

### Level Set Example with Different Viscosity

![Level Set Example](https://github.com/doyubkim/fluid-engine-dev/raw/main/doc/img/ls_bunny_drop.png "Level Set Example ")

### Smoke Simulation with Different Advection Methods

![Cubic-smoke Example](https://github.com/doyubkim/fluid-engine-dev/raw/main/doc/img/smoke_cubic.png "Cubic-smoke Example")
![Linear-smoke Example](https://github.com/doyubkim/fluid-engine-dev/raw/main/doc/img/smoke_linear.png "Linear-smoke Example")

### Point-to-Surface Examples

![Point-to-Surface Example](https://github.com/doyubkim/fluid-engine-dev/raw/main/doc/img/point_to_surface.png "Point-to-Surface Example")

> Top-left: spherical, top-right: SPH blobby, bottom-left: Zhu and Bridson's method, and bottom-right: Anisotropic kernel

## Developers

This repository is created and maintained by Doyub Kim (@doyubkim). Chris Ohk (@utilForever) is a co-developer of the framework since v1.3. [Many other contributors](https://github.com/doyubkim/fluid-engine-dev/graphs/contributors) also helped improving the codebase including Jefferson Amstutz (@jeffamstutz) who helped integrating Intel TBB and OpenMP backends.

## License

Jet is under the MIT license. For more information, check out [LICENSE.md](https://github.com/doyubkim/fluid-engine-dev/blob/main/LICENSE.md). Jet also utilizes other open source codes. Checkout [3RD_PARTY.md](https://github.com/doyubkim/fluid-engine-dev/blob/main/3RD_PARTY.md) for more details.

I am making my contributions/submissions to this project solely in my personal capacity and am not conveying any rights to any intellectual property of any third parties.

## Acknowledgement

We would like to thank [JetBrains](https://www.jetbrains.com/) for their support and allowing us to use their products for developing Jet Framework.

![JetBrains](doc/img/jetbrains.svg)
