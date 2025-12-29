<!-- Machine Summary Block -->
{"file":"docs/BUILD.md","purpose":"Comprehensive build guide for SimulationAutoTuner covering prerequisites, vcpkg setup, and platform-specific instructions."}

# Build Guide — SimulationAutoTuner

This guide provides detailed instructions for building SimulationAutoTuner from source on Windows and Linux.

## Table of Contents

- [Prerequisites](#prerequisites)
- [Quick Start](#quick-start)
- [Detailed Build Steps](#detailed-build-steps)
- [vcpkg Setup](#vcpkg-setup)
- [CMake Presets](#cmake-presets)
- [Platform-Specific Notes](#platform-specific-notes)
- [Troubleshooting](#troubleshooting)

---

## Prerequisites

### All Platforms

- **CMake 3.23 or later**
  - Download from https://cmake.org/download/
  - Or install via package manager

- **Git**
  - Required for cloning the repository and submodules
  - Download from https://git-scm.com/

- **Ninja Build System**
  - Install via package manager or https://ninja-build.org/
  - Used for faster, cross-platform builds

### Windows

- **Microsoft Visual Studio 2022**
  - Community Edition or higher
  - Install "Desktop development with C++" workload
  - Ensures MSVC compiler and Windows SDK are available

- **Developer Command Prompt**
  - Use "Developer Command Prompt for VS 2022" or "Developer PowerShell"
  - Provides MSVC toolchain environment

### Linux

- **GCC 9 or later** (or Clang 10+)
  ```bash
  # Ubuntu/Debian
  sudo apt-get install build-essential

  # Fedora
  sudo dnf install gcc gcc-c++
  ```

- **Ninja**
  ```bash
  # Ubuntu/Debian
  sudo apt-get install ninja-build

  # Fedora
  sudo dnf install ninja-build
  ```

---

## Quick Start

```bash
# Clone with submodules
git clone https://github.com/QuinnAho/sim-auto-tuner.git --recursive
cd sim-auto-tuner

# Bootstrap vcpkg (first time only)
git clone https://github.com/microsoft/vcpkg.git external/vcpkg
./external/vcpkg/bootstrap-vcpkg.sh  # Linux/macOS
# OR
.\external\vcpkg\bootstrap-vcpkg.bat # Windows

# Configure and build
cmake --preset Release
cmake --build --preset Release

# Run tests
./build/Release/bin/sat_cli_test --help
```

---

## Detailed Build Steps

### 1. Clone the Repository

```bash
git clone https://github.com/QuinnAho/sim-auto-tuner.git --recursive
cd sim-auto-tuner
```

The `--recursive` flag ensures all Git submodules are initialized (including legacy Jet dependencies).

### 2. Setup vcpkg (First Time Only)

SimulationAutoTuner uses vcpkg for dependency management. On first build, you need to bootstrap vcpkg:

**Linux/macOS:**
```bash
git clone https://github.com/microsoft/vcpkg.git external/vcpkg
./external/vcpkg/bootstrap-vcpkg.sh
```

**Windows:**
```cmd
git clone https://github.com/microsoft/vcpkg.git external/vcpkg
.\external\vcpkg\bootstrap-vcpkg.bat
```

vcpkg will automatically download and build the following dependencies:
- **spdlog** (logging library)
- **fmt** (formatting library)
- **CLI11** (command-line parsing)

### 3. Configure with CMake Presets

SimulationAutoTuner provides CMake presets for easy configuration:

```bash
# Release build (optimized)
cmake --preset Release

# Debug build (with symbols)
cmake --preset Debug
```

This command:
1. Reads `CMakePresets.json`
2. Configures vcpkg toolchain
3. Invokes vcpkg to install dependencies (if needed)
4. Generates Ninja build files in `build/<preset>/`

### 4. Build

```bash
cmake --build --preset Release
# or
cmake --build --preset Debug
```

Build output:
- Executables: `build/<preset>/bin/`
- Libraries: `build/<preset>/lib/`

### 5. Run

```bash
# Linux
./build/Release/bin/sat_cli_test --help

# Windows
.\build\Release\bin\sat_cli_test.exe --help
```

---

## vcpkg Setup

### What is vcpkg?

vcpkg is Microsoft's cross-platform C++ package manager. SimulationAutoTuner uses "manifest mode" where dependencies are declared in `vcpkg.json` and automatically installed during CMake configuration.

### Manifest Mode

The `vcpkg.json` file at the project root lists all dependencies:

```json
{
  "name": "simulationautotuner",
  "version": "0.1.0",
  "dependencies": [
    "spdlog",
    "fmt",
    "cli11"
  ]
}
```

Dependencies are installed to `vcpkg_installed/` (git-ignored) and linked via CMake's `find_package()`.

### Cache and Performance

vcpkg caches built packages globally at:
- **Windows**: `%LOCALAPPDATA%\vcpkg\archives`
- **Linux**: `~/.cache/vcpkg/archives`

This means dependencies are only built once and reused across projects.

---

## CMake Presets

SimulationAutoTuner uses CMake 3.23+ presets defined in `CMakePresets.json`:

| Preset    | Generator | Build Type | Output Dir         |
|-----------|-----------|-----------|--------------------|
| `Debug`   | Ninja     | Debug     | `build/Debug/`     |
| `Release` | Ninja     | Release   | `build/Release/`   |

### Custom Configuration

You can override preset values:

```bash
# Use a different build directory
cmake --preset Release -B build/my-custom-dir

# Add extra CMake options
cmake --preset Release -DSAT_ENABLE_TESTS=ON
```

---

## Platform-Specific Notes

### Windows

**Recommended**: Use "Developer Command Prompt for VS 2022" or "Developer PowerShell for VS 2022" to ensure MSVC toolchain is in PATH.

If using regular PowerShell/CMD:
```cmd
# Load MSVC environment
"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

# Then proceed with cmake commands
cmake --preset Release
```

### Linux

**Install Ninja** if not already present:
```bash
sudo apt-get install ninja-build  # Ubuntu/Debian
sudo dnf install ninja-build       # Fedora
```

**Compiler Selection**: CMake will auto-detect GCC. To use Clang:
```bash
export CC=clang
export CXX=clang++
cmake --preset Release
```

---

## Troubleshooting

### "vcpkg not found" errors

If CMake can't find vcpkg:
```bash
# Ensure vcpkg is bootstrapped
./external/vcpkg/bootstrap-vcpkg.sh  # or .bat on Windows

# Verify vcpkg.exe/vcpkg exists
ls external/vcpkg/vcpkg  # Linux
dir external\vcpkg\vcpkg.exe  # Windows
```

### "Ninja not found"

Install Ninja via package manager or download from https://ninja-build.org/

**Windows (choco):**
```cmd
choco install ninja
```

**Linux:**
```bash
sudo apt-get install ninja-build
```

### Dependency build failures

vcpkg sometimes fails on network issues. Retry:
```bash
# Clean vcpkg cache
rm -rf vcpkg_installed/

# Reconfigure (will re-download dependencies)
cmake --preset Release
```

### "No matching preset found"

Ensure you're using CMake 3.23+:
```bash
cmake --version
```

Upgrade if needed:
- Windows: Download MSI from cmake.org
- Linux: Use Kitware's APT repository or build from source

---

## Build Variants

### Clean Build

To start fresh:
```bash
# Remove build directory
rm -rf build/

# Reconfigure and rebuild
cmake --preset Release
cmake --build --preset Release
```

### Verbose Build

To see full compiler commands:
```bash
cmake --build --preset Release --verbose
```

### Parallel Builds

Ninja automatically parallelizes. To limit:
```bash
cmake --build --preset Release -j 4  # Use 4 cores
```

---

## Next Steps

- Read [CLI_REFERENCE.md](CLI_REFERENCE.md) for command-line options
- See [ARCHITECTURE.md](ARCHITECTURE.md) for project structure
- Check [CODING_STYLE.md](CODING_STYLE.md) before contributing

---

**Build Issues?** File an issue at https://github.com/QuinnAho/sim-auto-tuner/issues
