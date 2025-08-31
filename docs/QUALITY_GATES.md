
# Quality Gates Overview
- **Security**: CodeQL, Semgrep, Gitleaks, Trivy, Grype, Dependency Review, OSV-Scanner, license allowlist, REUSE.
- **Supply chain**: SLSA provenance, cosign signing, SBOM (SPDX/CycloneDX) + diff, VEX template.
- **Build**: Reproducibility (SOURCE_DATE_EPOCH, diffoscope), Hardened flags, PIE/RELRO/NOW, CFG, NX/DynamicBase on Windows.
- **Testing**: CTest smoke, fuzzing (libFuzzer + ClusterFuzzLite), coverage (lcov + gate).
- **Performance**: Hyperfine, perf budgets, IPO/LTO, PGO playbook.
- **Docs**: MkDocs to Pages, link check (Lychee), style (Vale), inclusive language (alex).
- **Governance**: DCO, CODEOWNERS, CoC, issue/PR templates, Release-Please.
