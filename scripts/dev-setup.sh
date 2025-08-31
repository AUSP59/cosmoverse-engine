
#!/usr/bin/env bash
set -euo pipefail
echo "Installing common dev tools..."
if command -v apt-get >/dev/null; then
  sudo apt-get update
  sudo apt-get install -y build-essential cmake ninja-build clang-format cppcheck doxygen graphviz gcovr
fi
echo "Done."
