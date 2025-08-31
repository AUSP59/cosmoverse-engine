
# Signing & Verification
- Containers are **keyless-signed** (Sigstore/cosign). Verify with:
  ```bash
  scripts/verify_container_signature.sh ghcr.io/your-org/cosmoverse-engine:latest
  ```
- Release assets are **signed blobs**. Verify with:
  ```bash
  scripts/verify_release_asset.sh cosmoverse-1.0.0-linux-amd64.tar.xz
  ```
