
# Threat Model (initial)
- Assets: source code, artifacts, SBOM/provenance, release credentials.
- Actors: maintainers, contributors, CI runners, external consumers.
- Risks: supply chain attacks, secret leakage, malicious PRs, dependency compromise.
- Controls: DCO, CODEOWNERS, Signed tags/images (cosign), SLSA provenance, SBOM, SAST, license gate, branch protection, permissions hardening, fuzzing/sanitizers, perf/size gates.
- Gaps (operational): require org-level settings (2FA, SSO, key management).
