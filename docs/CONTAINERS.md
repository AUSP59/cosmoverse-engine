
# Containers
- Development: `Dockerfile` (root) and `.devcontainer/` for VS Code.
- Runtime: `Dockerfile.rootless` and `Dockerfile.distroless` for minimal non-root execution.
- Images are signed (cosign keyless) in release workflow; SBOM available.

- Run with seccomp: `docker run --security-opt seccomp=deploy/seccomp/cosmoverse-seccomp.json ...`


## Distroless images
Use the provided `docker/Dockerfile.distroless` with a **pinned digest**. Replace `REPLACE_WITH_REAL_DIGEST` with an audited digest obtained via:
```bash
crane digest gcr.io/distroless/cc-debian12:latest
```
Verify provenance and signature (cosign) before pinning.
