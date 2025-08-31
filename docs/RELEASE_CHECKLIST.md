
# Release Checklist
- [ ] All CI green (sanitizers, fuzz build, perf/size/doc/repro gates)
- [ ] `release-please` PR generated and merged
- [ ] SBOM uploaded (SPDX & CycloneDX)
- [ ] Container built & **signed** (cosign keyless)
- [ ] Assets **signed** (cosign sign-blob)
- [ ] Changelogs, docs, and version bump verified
- [ ] Announce with links to signatures & provenance
