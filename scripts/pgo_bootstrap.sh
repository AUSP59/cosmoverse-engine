
#!/usr/bin/env bash
set -euo pipefail
# 1) Build with PGO generate
cmake -S . -B build-pgo -DCMAKE_BUILD_TYPE=Release -DCOSMO_PGO=GENERATE
cmake --build build-pgo -j
# 2) Run representative workload (replace with real commands)
./build-pgo/bin/cosmoverse bench 1000000 0 || true
# 3) Rebuild using PGO profiles
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCOSMO_PGO=USE -DCOSMO_PGO_DIR="$(pwd)/build-pgo/pgo"
cmake --build build -j
