<!-- Machine Summary Block -->
{"file":"docs/DEPENDENCIES.md","purpose":"Documents all third-party dependencies used in SimulationAutoTuner including versions, licenses, and purposes."}

# Dependencies — SimulationAutoTuner

This document lists all third-party libraries and tools used by SimulationAutoTuner.

## Table of Contents

- [Modern Dependencies (vcpkg)](#modern-dependencies-vcpkg)
- [Legacy Dependencies (Git Submodules)](#legacy-dependencies-git-submodules)
- [Build Tools](#build-tools)
- [License Summary](#license-summary)

---

## Modern Dependencies (vcpkg)

These dependencies are managed via vcpkg manifest mode (`vcpkg.json`) and automatically installed during CMake configuration.

### spdlog

- **Version**: 1.16.0
- **License**: MIT
- **Purpose**: Fast C++ logging library
- **Usage**: Core logging infrastructure (`sim/logging.cpp`)
- **Repository**: https://github.com/gabime/spdlog
- **CMake**: `find_package(spdlog CONFIG REQUIRED)`

**Why spdlog?**
- Header-only or compiled mode
- Extremely fast (asynchronous logging)
- Formatted output with fmt integration
- Multiple sinks (stdout, file, rotating files)

### fmt

- **Version**: 12.1.0
- **License**: MIT
- **Purpose**: Modern C++ formatting library (C++20 `std::format` backport)
- **Usage**: String formatting throughout codebase
- **Repository**: https://github.com/fmtlib/fmt
- **CMake**: `find_package(fmt CONFIG REQUIRED)`

**Why fmt?**
- Type-safe alternative to printf
- Fast compile times
- Used by spdlog internally
- Basis for C++20 `std::format`

### CLI11

- **Version**: 2.6.1
- **License**: BSD-3-Clause
- **Purpose**: Command-line parser
- **Usage**: CLI argument parsing (`app/cli_config.cpp`)
- **Repository**: https://github.com/CLIUtils/CLI11
- **CMake**: `find_package(CLI11 CONFIG REQUIRED)`

**Why CLI11?**
- Header-only
- Type-safe
- Composable command structure
- Automatic `--help` generation
- Validation built-in

---

## Legacy Dependencies (Git Submodules)

These are from the original Jet framework and located in `external/`. Currently **disabled** in the build (`SAT_ENABLE_LEGACY_SRC=OFF`) but preserved for future migration.

### GoogleTest

- **Location**: `external/googletest`
- **License**: BSD-3-Clause
- **Purpose**: C++ unit testing framework
- **Status**: Submodule (disabled)
- **Repository**: https://github.com/google/googletest

### Google Benchmark

- **Location**: `external/googlebenchmark`
- **License**: Apache-2.0
- **Purpose**: Microbenchmarking library
- **Status**: Submodule (disabled)
- **Repository**: https://github.com/google/benchmark

### pybind11

- **Location**: `external/pybind11`
- **License**: BSD-3-Clause
- **Purpose**: Python bindings for C++
- **Status**: Submodule (disabled, `SAT_ENABLE_PYTHON_BINDINGS=OFF`)
- **Repository**: https://github.com/pybind/pybind11

### Clara

- **Location**: `external/Clara`
- **License**: BSL-1.0
- **Purpose**: Legacy CLI parser (replaced by CLI11)
- **Status**: Submodule (disabled)
- **Repository**: https://github.com/catchorg/Clara

### tinyobj

- **Location**: `external/tinyobj`
- **License**: MIT
- **Purpose**: OBJ file loader
- **Status**: Submodule (disabled)
- **Repository**: https://github.com/tinyobjloader/tinyobjloader

### cnpy

- **Location**: `external/cnpy`
- **License**: MIT
- **Purpose**: NumPy file I/O
- **Status**: Submodule (disabled)

### pystring

- **Location**: `external/pystring`
- **License**: BSD-3-Clause
- **Purpose**: Python-like string operations in C++
- **Status**: Submodule (disabled)

---

## Build Tools

### vcpkg

- **Version**: Latest (bootstrapped)
- **License**: MIT
- **Purpose**: C++ package manager
- **Location**: `external/vcpkg` (git-ignored)
- **Repository**: https://github.com/microsoft/vcpkg

**Setup**:
```bash
git clone https://github.com/microsoft/vcpkg.git external/vcpkg
./external/vcpkg/bootstrap-vcpkg.sh  # or .bat on Windows
```

### CMake

- **Minimum Version**: 3.23
- **Purpose**: Build system generator
- **Download**: https://cmake.org/download/

### Ninja

- **Purpose**: Fast build system (replacement for Make/MSBuild)
- **Why Ninja?**:
  - Cross-platform consistency
  - Faster incremental builds
  - Cleaner error output
- **Install**:
  ```bash
  # Ubuntu/Debian
  sudo apt-get install ninja-build

  # Windows (chocolatey)
  choco install ninja
  ```

---

## License Summary

| Dependency   | License        | Commercial Use | Attribution Required |
|--------------|----------------|----------------|----------------------|
| spdlog       | MIT            | Yes            | Yes (in docs)        |
| fmt          | MIT            | Yes            | Yes (in docs)        |
| CLI11        | BSD-3-Clause   | Yes            | Yes (in docs)        |
| GoogleTest   | BSD-3-Clause   | Yes            | Yes (in docs)        |
| Benchmark    | Apache-2.0     | Yes            | Yes (in docs)        |
| pybind11     | BSD-3-Clause   | Yes            | Yes (in docs)        |
| Clara        | BSL-1.0        | Yes            | No                   |
| tinyobj      | MIT            | Yes            | Yes (in docs)        |
| cnpy         | MIT            | Yes            | Yes (in docs)        |
| pystring     | BSD-3-Clause   | Yes            | Yes (in docs)        |

**All dependencies are permissively licensed and compatible with commercial use.**

---

## Adding New Dependencies

### Via vcpkg (Recommended)

1. Search for package:
   ```bash
   ./external/vcpkg/vcpkg search <package-name>
   ```

2. Add to `vcpkg.json`:
   ```json
   {
     "dependencies": [
       "spdlog",
       "fmt",
       "cli11",
       "your-new-package"
     ]
   }
   ```

3. Reconfigure CMake:
   ```bash
   cmake --preset Release
   ```

4. Update this document with the new dependency

### Via Git Submodule (Legacy)

Only use submodules if the library is not available in vcpkg.

```bash
git submodule add https://github.com/user/repo.git external/repo
git submodule update --init --recursive
```

---

## Dependency Graph

```
SimulationAutoTuner
├── spdlog (logging)
│   └── fmt (formatting)
├── CLI11 (CLI parsing)
└── [Legacy Jet dependencies - currently disabled]
    ├── GoogleTest
    ├── Google Benchmark
    ├── pybind11
    └── tinyobj
```

---

## Security & Updates

### Vulnerability Scanning

vcpkg packages are regularly scanned for known vulnerabilities. To update dependencies:

```bash
# Update vcpkg itself
cd external/vcpkg
git pull
./bootstrap-vcpkg.sh  # or .bat

# Update packages
cd ../..
rm -rf vcpkg_installed/
cmake --preset Release  # Re-installs latest versions
```

### Dependency Pinning

Versions are specified in `vcpkg.json`. To pin specific versions, use version constraints:

```json
{
  "dependencies": [
    {
      "name": "spdlog",
      "version>=": "1.16.0"
    }
  ]
}
```

---

## Future Dependencies (Planned)

The following dependencies are planned for future milestones:

- **Dear ImGui** - Immediate-mode GUI library (Milestone 1)
- **GLFW** - OpenGL window/context management (Milestone 1)
- **glad** - OpenGL loader (Milestone 1)
- **libtorch** or **ONNX Runtime** - ML inference (Milestone 3+)

---

**Questions?** See [BUILD.md](BUILD.md) for build instructions or file an issue at https://github.com/QuinnAho/sim-auto-tuner/issues
