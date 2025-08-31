# Contributing to COSMOVERSE ENGINE

Thanks for your interest in contributing! This project is an **English-only** repository under the **Apache-2.0** license. By participating you agree to abide by the [Code of Conduct](./CODE_OF_CONDUCT.md).

Maintainer: **@AUSP59** · **alanursapu@gmail.com**

---

## Quick start (development)

```bash
# 1) Fork & clone your fork
git clone https://github.com/<you>/cosmoverse-engine.git
cd cosmoverse-engine
git remote add upstream https://github.com/AUSP59/cosmoverse-engine.git

# 2) Dev environment (choose one)
# Devcontainer: open in VS Code → "Reopen in Container"
# or Nix:
nix develop

# 3) Build, test, format, lint
cmake -S . -B build -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCOSMO_USE_CCACHE=ON -DCOSMO_PCH=ON
cmake --build build -j
ctest --test-dir build --output-on-failure
pre-commit install
pre-commit run --all-files
Recommended debug runs
bash
Copiar código
# Sanitizers (choose one): address | undefined | thread
cmake -S . -B build-asan -DCMAKE_BUILD_TYPE=Debug -DCOSMO_SANITIZE=address
cmake --build build-asan -j && ctest --test-dir build-asan --output-on-failure

# Fuzz (best effort)
cmake --build build -j --target fuzz_cosmo_api || true
./build/fuzz_cosmo_api || true
How we work
English only.

Conventional Commits for titles (e.g. feat: add SIMD kernel).

DCO sign-off required for every commit.

Small PRs are easier to review; large changes: open an issue first (or RFC/ADR).

We squash-merge PRs (commit history stays clean).

Branch naming: feat/..., fix/..., docs/..., chore/....

See also: GOVERNANCE.md, BRANCHING_MODEL.md, CONTRIBUTOR_LADDER.md.

DCO (Developer Certificate of Origin)
Every commit must include a Signed-off-by: line matching the commit author:

bash
Copiar código
git commit -s -m "feat: add vectorized blend kernel"
# or add manually at the end of the message:
# Signed-off-by: Your Name <you@example.com>
The DCO bot/workflow will flag commits that lack sign-off.

PR checklist (please read)
 Title follows Conventional Commits.

 DCO sign-off present in every commit.

 Code builds on Linux/macOS/Windows (CI Quick covers Linux).

 Tests: add/extend unit tests (tests/) and run ctest.

 If touching performance-critical code, add/refresh benchmarks and note results.

 clang-format pass; run pre-commit run --all-files.

 Public headers keep stable C API (no breaking changes without discussion).

 Docs updated (MkDocs nav if new topics).

 If adding a dependency: license allowlisted, SBOM updated, REUSE headers present.

Coding standards
C++20, prefer standard facilities; avoid non-portable extensions.

Headers under include/cosmoverse/ are public API; keep them minimal and well-documented.

Keep functions short; prefer std::span, std::string_view, RAII, and noexcept where applicable.

Use our logger (include/cosmoverse/log.hpp) for diagnostics; no raw printf in library code.

Run formatters/linters via pre-commit. Style controlled by .clang-format, .editorconfig.

Testing & quality
Unit tests with CTest. Place sources under tests/.

Sanitizers (ASan/UBSan/TSan) in debug builds.

Fuzzing: targets like fuzz_cosmo_api (best effort). Add corpus/minimizers for new parsers.

Coverage: if you add large features, include tests exercising new paths.

Performance: keep binary size & perf within budgets; if you regress, document rationale and add tests/benchmarks.

Performance & CPU features
If you add CPU-specific code (SSE2/AVX2/NEON):

Put portable implementation first; add optimized kernels behind the runtime dispatcher (include/cosmoverse/cpu_dispatch.hpp).

Guard with -DCOSMO_CPU=sse2;avx2;neon options; keep clean fallbacks.

Provide a micro-benchmark snippet and results in the PR description.

Documentation
Docs live in docs/ (MkDocs Material).

Update or add pages and link them in mkdocs.yml nav.

Use inclusive, clear language; Vale/alex/Pa11y run in CI (advisory).

Examples belong in examples/ and should compile.

Local preview:

bash
Copiar código
pip install mkdocs-material
mkdocs serve  # http://127.0.0.1:8000
Security
Do not file public issues for vulnerabilities.

Report privately via GitHub Security Advisories or email alanursapu@gmail.com.

See the full policy: .github/SECURITY.md.

No secrets in code/CI. Gitleaks/Semgrep run in CI.

Dependencies & licensing
License allowlist: Apache-2.0, MIT, BSD-2/3-Clause, ISC, MPL-2.0, Zlib, Unicode-DFS-2016.

Avoid copyleft (e.g., GPL/LGPL/AGPL) unless cleared in an issue first.

Add SPDX headers to new sources (scripts/add_spdx.py helps).

If vendoring, include license file and update THIRD_PARTY_NOTICES.txt.

Release notes
We use GitHub Releases; include a short change summary in your PR body.

Breaking changes require:

Migration notes in PR

Docs update

Version bump rationale (SemVer)

Maintainer approval

Running the full CI locally (optional)
bash
Copiar código
# Format, lint, SPDX, markdown
pre-commit run --all-files

# Linux build + tests
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build -j && ctest --test-dir build

# Sanitizers (pick one)
cmake -S . -B build-ubsan -DCMAKE_BUILD_TYPE=Debug -DCOSMO_SANITIZE=undefined && cmake --build build-ubsan -j && ctest --test-dir build-ubsan
Communication
Open an Issue for bugs/feature requests.

Use Discussions for Q&A/ideas.

For sensitive topics (security/coordinated disclosure), use the contacts above.

Thank you!
Your contributions make COSMOVERSE ENGINE better for everyone.