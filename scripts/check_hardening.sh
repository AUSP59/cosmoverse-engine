
#!/usr/bin/env bash
set -euo pipefail
bin="${1:-build/bin/cosmoverse}"
echo "Checking: $bin"
if command -v checksec >/dev/null 2>&1; then
  checksec --file="$bin" || true
else
  echo "checksec not installed; skipping detailed hardening checks."
fi
