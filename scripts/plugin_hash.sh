
#!/usr/bin/env bash
set -euo pipefail
file="${1:?usage: $0 <plugin-file>}"
if command -v sha256sum >/dev/null 2>&1; then
  sha256sum "$file" | awk '{print tolower($1)}'
elif command -v shasum >/dev/null 2>&1; then
  shasum -a 256 "$file" | awk '{print tolower($1)}'
else
  echo "no sha256 tool found" >&2; exit 1
fi
