
# Architecture Overview
- **Core** (`src/`): C++20 library with hidden symbols by default; public API under `include/cosmoverse/` and C API under `include/cosmoverse/c_api.h`.
- **CLI** (`apps/`): thin wrapper; outputs human-friendly text and `--json` for machine use.
- **Plugins** (`src/core/plugin_loader.*`, `plugins/`): C ABI with versioned interface and optional SHA-256 allowlist; `cosmo_plugin_runner` allows process isolation.
- **Bindings** (`bindings/`): C/Python/Rust/Node/Go; ABI stable across minor versions.
- **Build**: CMake primary; CI covers Linux/macOS/Windows + musl + Emscripten + WASI + Nix + mobile (advisory).
- **Security**: hardening flags, sanitizers, fuzzing, SBOM, SLSA provenance, cosign signatures, scanners and gates.
