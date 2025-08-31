
#!/usr/bin/env bash
set -euo pipefail
# Build inside a minimal container to reduce host influence (needs docker)
img="debian:stable-slim"
docker run --rm -t -v "$PWD":/src -w /src "$img" /bin/bash -lc '
  apt-get update && apt-get install -y build-essential cmake ninja-build git ca-certificates && update-ca-certificates
  bash scripts/set_repro_epoch.sh
  cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
  cmake --build build -j
  cmake --install build --prefix /out || true
'
