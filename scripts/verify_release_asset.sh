
#!/usr/bin/env bash
set -euo pipefail
file="${1:?usage: $0 <asset>}"
cosign verify-blob --certificate "${file}.pem" --signature "${file}.sig" "$file"
