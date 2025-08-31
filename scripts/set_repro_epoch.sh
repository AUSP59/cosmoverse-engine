
#!/usr/bin/env bash
# Set SOURCE_DATE_EPOCH to the last commit timestamp or fallback to a fixed value
set -euo pipefail
if git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
  export SOURCE_DATE_EPOCH=$(git log -1 --pretty=%ct)
else
  export SOURCE_DATE_EPOCH=1700000000
fi
echo "SOURCE_DATE_EPOCH=$SOURCE_DATE_EPOCH"
