
#!/usr/bin/env bash
set -euo pipefail
mkdir -p dist
shopt -s nullglob
: > dist/checksums.txt
for f in build/bin/* build/lib*/* 2>/dev/null; do
  [ -f "$f" ] || continue
  sha256sum "$f" >> dist/checksums.txt
done
echo "Wrote dist/checksums.txt"
