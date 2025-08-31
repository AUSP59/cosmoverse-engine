
# Release Artifacts
- Binaries: per-OS archives + checksums; signed with cosign (sign-blob).
- SBOMs: SPDX & CycloneDX uploaded to releases.
- Container: GHCR signed (keyless) + SLSA provenance.
- Source: deterministic tarball via `make dist-src`.
