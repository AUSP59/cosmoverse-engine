
#!/usr/bin/env bash
set -euo pipefail
echo "COSMOVERSE doctor"
command -v cmake || { echo "cmake missing"; exit 1; }
command -v c++ || { echo "C++ compiler missing"; exit 1; }
cmake --version; c++ --version || true
