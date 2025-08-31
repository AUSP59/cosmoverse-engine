# SPDX-License-Identifier: Apache-2.0
#!/usr/bin/env bash
set -euo pipefail
if command -v clang-format >/dev/null 2>&1; then
git ls-files '*.hpp' '*.h' '*.cpp' | xargs clang-format -i
else
echo 'clang-format not found.'
fi
