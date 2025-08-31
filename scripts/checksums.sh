
#!/usr/bin/env bash
set -euo pipefail
dir="${1:-dist}"
mkdir -p "$dir"
( cd "$dir" && sha256sum * 2>/dev/null || shasum -a 256 * 2>/dev/null ) > "$dir/SHA256SUMS.txt" || true
echo "Wrote $dir/SHA256SUMS.txt (if artifacts exist)"
