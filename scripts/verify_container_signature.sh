
#!/usr/bin/env bash
set -euo pipefail
img="${1:?usage: $0 ghcr.io/ORG/REPO:TAG}"
export COSIGN_EXPERIMENTAL=1
cosign verify --certificate-oidc-issuer https://token.actions.githubusercontent.com "$img"
