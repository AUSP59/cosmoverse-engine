
#!/usr/bin/env bash
set -euo pipefail
# Check that all commits in the PR have a Signed-off-by line
range="${1:-HEAD~20..HEAD}"
commits=$(git rev-list $range || true)
ok=0; fail=0
for c in $commits; do
  if git log -1 --pretty=%B $c | grep -qi '^Signed-off-by: '; then
    ok=$((ok+1))
  else
    echo "::error::Commit $c missing Signed-off-by trailer"
    fail=$((fail+1))
  fi
done
[ $fail -eq 0 ]
