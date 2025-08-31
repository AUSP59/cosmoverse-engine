
# COSMOVERSE ENGINE — Technical Whitepaper (non-marketing)

## Scope
This document describes the architecture, security posture, build & release process, and portability/performance model of the open-source project as currently implemented.

## Architecture
- **Core library (C++20)** with C API boundary and default hidden visibility; stable ABI guarded via export map and ABI compliance checks.
- **CLI** thin layer with `--json` outputs validated by JSON Schemas.
- **Plugin system (C ABI)** with ABI versioning and optional SHA-256 allowlist.
- **Bindings** for C, Python, Rust, Node, Go (+ samples for Java/.NET/Swift).
- **Docs**: Doxygen (API) + MkDocs (site), manpage & completions.

## Security & Supply Chain
- Hardening defaults (RELRO/NOW/PIE/FORTIFY/cf-protection), sanitizers/ASAN/UBSAN/TSAN, fuzzing.
- SBOM (SPDX/CycloneDX), SLSA provenance, cosign signatures, deterministic builds (SOURCE_DATE_EPOCH + diffoscope).
- Scanners: CodeQL/Semgrep, Trivy/Grype, Gitleaks, OSV, Dependency Review, OpenSSF Scorecards.
- Container: rootless/distroless/static options + seccomp profile.

## Portability & Reproducibility
- CI on Linux/macOS/Windows + Alpine/musl + Emscripten + WASI + Nix.
- CMake primary; also Bazel/Meson/Nix manifests; package exports; DEB/RPM/DMG; vcpkg/Conan/pkg-config.

## Performance
- Benchmarks include micro-harness and optional Google Benchmark.
- Perf/size gates in CI. LTO/PGO options available via CMake cache.

## Governance
- DCO + Conventional Commits + CODEOWNERS + release-please for versioning.
- Policies: SECURITY, PRIVACY, ACCESSIBILITY, API STABILITY, EOL, TRUST.

## Limitations & Future Work (non-fiction)
- Domain algorithms are out of scope until contributed (physics, simulation).
- Formal external audits require independent parties and budget.
