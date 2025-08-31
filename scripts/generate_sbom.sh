
#!/usr/bin/env bash
set -euo pipefail
OUT=${1:-sbom.spdx.json}
if command -v syft >/dev/null 2>&1; then
  syft . -o spdx-json > "$OUT"
else
  echo '{"spdxVersion":"SPDX-2.3","name":"cosmoverse","creationInfo":{"created":"1970-01-01T00:00:00Z"}}' > "$OUT"
  echo "syft not found; wrote minimal SPDX stub to $OUT" >&2
fi
