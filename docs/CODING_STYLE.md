<!-- Machine Summary Block -->
{"file":"docs/CODING_STYLE.md","purpose":"Documents formatting and linting conventions enforced via clang-format/clang-tidy."}

# Coding Style Guidelines

SimulationAutoTuner adopts a modernized Google-derived style tuned for readability and deterministic diffs.

## Formatting (`.clang-format`)

- Base on the Google profile with project-specific offsets for access modifiers and bracket alignment.
- Stick to spaces (IndentWidth 2 unless overridden in `.clang-format`); never use tabs.
- Keep includes ordered logically: local headers last, standard library first.
- Run `clang-format` (LLVM 19+) before committing; the repo stores a ready-to-use preset.
  ```powershell
  & "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\Llvm\bin\clang-format.exe" -i path\to\file.cpp
  ```

## Linting (`.clang-tidy`)

- `.clang-tidy` enables bugprone analyzer checks plus basic modernization/performance rules.
- The header filter scopes findings to `app/`, `sim/`, and legacy `src/` so vendor code is ignored.
- Identifier-naming options enforce lower_case namespaces, CamelCase types, camelBack methods, and `_` suffix for private members.
- Invoke clang-tidy after generating `compile_commands.json` via CMake presets:
  ```powershell
  cmake --preset Release
  & "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\Llvm\bin\clang-tidy.exe" -p build/Release app\example.cpp
  ```

## Reviewer Expectations

- New code must compile cleanly under both Debug/Release presets.
- Formatting/linting issues block merges; run both tools locally before opening a PR.
- Document any intentional deviations inside the affected file’s Machine Summary Block.
