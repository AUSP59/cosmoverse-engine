
#!/usr/bin/env bash
set -euo pipefail
base="${1:-}"
head="${2:-HEAD}"
if [ -z "$base" ]; then
  range="$head"
else
  range="$base..$head"
fi
missing=0
while read -r sha; do
  if ! git show -s --format=%B "$sha" | grep -qiE '^Signed-off-by: .+ <.+@.+>$'; then
    echo "Commit $sha missing DCO Signed-off-by line"
    missing=$((missing+1))
  fi
done < <(git rev-list "$range")
if [ "$missing" -gt 0 ]; then
  echo "$missing commit(s) missing DCO"
  exit 1
fi
echo "All commits have DCO sign-off"
