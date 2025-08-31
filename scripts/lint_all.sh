# SPDX-License-Identifier: Apache-2.0
#!/usr/bin/env bash
set -euo pipefail
if command -v clang-tidy >/dev/null 2>&1; then
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
clang-tidy -p build $(git ls-files '*.cpp')
else
echo 'clang-tidy not found.'
fi
