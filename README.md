# COSMOVERSE ENGINE

Production-grade, portable **C++20** engine toolkit with world-class security, supply chain integrity, documentation, and operational maturity. English-only project.

[![CI Quick](https://github.com/AUSP59/cosmoverse-engine/actions/workflows/ci-quick.yml/badge.svg)](https://github.com/AUSP59/cosmoverse-engine/actions/workflows/ci-quick.yml)
[![Sanitizers](https://github.com/AUSP59/cosmoverse-engine/actions/workflows/sanitizers.yml/badge.svg)](https://github.com/AUSP59/cosmoverse-engine/actions/workflows/sanitizers.yml)
[![CodeQL](https://github.com/AUSP59/cosmoverse-engine/actions/workflows/codeql.yml/badge.svg)](https://github.com/AUSP59/cosmoverse-engine/actions/workflows/codeql.yml)
[![Docs](https://github.com/AUSP59/cosmoverse-engine/actions/workflows/docs-pages.yml/badge.svg)](https://github.com/AUSP59/cosmoverse-engine/actions/workflows/docs-pages.yml)
[![OpenSSF Scorecard](https://github.com/AUSP59/cosmoverse-engine/actions/workflows/scorecard.yml/badge.svg)](https://github.com/AUSP59/cosmoverse-engine/actions/workflows/scorecard.yml)
[![REUSE](https://img.shields.io/badge/REUSE-compliant-brightgreen)](https://reuse.software/)

---

## Highlights

- **Modern C++20**, strict warnings, hardening flags for Linux/macOS/Windows.
- **Stable C API** + plugin ABI (SHA-256 allowlist), symbol visibility & version scripts.
- **Quality & testing**: CTest, **Sanitizers** (ASan/UBSan/TSan), **fuzzing** (libFuzzer + ClusterFuzzLite), **coverage** gate, perf recorder & budget.
- **Security & supply chain**: CodeQL, Semgrep, Gitleaks, OSV/Trivy/Grype, **SBOM** (SPDX/CycloneDX), **SLSA provenance**, **cosign** signatures, **REUSE**, **DCO**, **OpenSSF Scorecard**.
- **Reproducibility**: `SOURCE_DATE_EPOCH`, diffoscope, reprotest, **Nix dev shell**.
- **Performance**: IPO/LTO, Unity builds, optional **PGO**, CPU feature toggles (`sse2;avx2;neon`) with runtime dispatch.
- **Ops & dist**: Distroless container, multi-arch builds (amd64/arm64), Helm chart, systemd/launchd/Windows service, Docker Compose (no-net, RO FS, seccomp).
- **Docs & governance**: MkDocs Material (Pages), accessibility checks (Pa11y), prose style (Vale), inclusive language (alex), link check (Lychee), CoC, CONTRIBUTING (+DCO), GOVERNANCE, MAINTAINERS, incident response, threat model, policies.

---

## Quick start

```bash
# Linux/macOS
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
ctest --test-dir build --output-on-failure
./build/bin/cosmoverse --help
Windows (MSVC Developer Prompt):

bat
Copiar código
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
build\bin\Release\cosmoverse.exe --help
Install / Package
CPack (archives/bundles): cmake --build build -j && cpack --config build/CPackConfig.cmake

pkg-config / CMake exports: find_package(cosmoverse CONFIG REQUIRED) or pkg-config --cflags --libs cosmoverse

Containers:

bash
Copiar código
docker run --rm ghcr.io/ausp59/cosmoverse-engine:latest --help
Helm:

bash
Copiar código
helm install cosmoverse charts/cosmoverse
See docs/PACKAGING.md, charts/, and docker/ for details.

Build options (CMake)
bash
Copiar código
# Typical dev build
cmake -S . -B build -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DCOSMO_USE_CCACHE=ON -DCOSMO_PCH=ON -DCOSMO_CPU="sse2;avx2"
COSMO_CPU: sse2;avx2;neon (semicolon-separated)

COSMO_PCH: Precompiled headers (OFF/ON)

COSMO_SANITIZE: address|undefined|thread (dev only)

PGO: see scripts/pgo_bootstrap.sh and docs/PERFORMANCE_OPTIMIZATION.md

Observability
Lightweight logger (include/cosmoverse/log.hpp)
Env: COSMO_LOG=trace|debug|info|warn|error|off, COSMO_LOG_JSON=1

Optional OpenTelemetry wrapper (include/cosmoverse/otel.hpp) auto-enables if SDK present.

Documentation
Local preview: mkdocs serve → http://127.0.0.1:8000

Published via GitHub Pages (workflow docs-pages.yml).

Accessibility checks (Pa11y), style (Vale), inclusive language (alex), links (Lychee).

Security
Report privately via GitHub Security Advisories or email alanursapu@gmail.com.

Policy: .github/SECURITY.md · Safe-harbor · CVE via GitHub CNA.

Verify releases:

bash
Copiar código
cosign verify ghcr.io/ausp59/cosmoverse-engine:TAG \
  --certificate-identity-regexp 'github.com/AUSP59/cosmoverse-engine' \
  --certificate-oidc-issuer 'https://token.actions.githubusercontent.com'
SBOM & provenance attached to Releases.

Contributing
We welcome issues and PRs! Please read:

CONTRIBUTING.md (DCO required; sign commits)

CODE_OF_CONDUCT.md

GOVERNANCE.md

docs/CONTRIBUTOR_LADDER.md

Dev environment: DevContainer or Nix (nix develop).
Hooks: pre-commit install (format, SPDX, lint).

CI & checks
CI Quick (Linux build + CTest) — fast green indicator.

Sanitizers, CodeQL, Scorecard, linters, reproducibility, container scan, docs a11y.

Many checks are advisory initially to avoid false ❌ on a new repo.
See docs/CHECKS_ADVISORY.md & docs/TROUBLESHOOTING_CI.md to make them blocking and mark as required.

Support matrix (indicative)
OS	Arch	Compiler	Min
Ubuntu LTS	x86_64	GCC/Clang	10/12
macOS 13+	x86_64	AppleClang	14
Windows 10+	x86_64	MSVC (Visual Studio)	19.30
Alpine 3.18+	x86_64	GCC (musl)	12
Linux arm64	arm64	GCC/Clang	12/14

Details: docs/SUPPORT_MATRIX.md.

Releases
Tag vX.Y.Z to trigger Release pipeline (multi-OS artifacts, checksums, SBOM, cosign signatures, SLSA provenance).
Homebrew/Chocolatey/WinGet templates in packaging/.

License & citation
Apache-2.0 — see LICENSE, NOTICE.

Cite via CITATION.cff.

AUTHORS lists contributors.

Maintainers
@AUSP59 · alanursapu@gmail.com
Open an issue or use the discussions tab for questions.