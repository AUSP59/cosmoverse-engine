
#!/usr/bin/env bash
set -euo pipefail
prefix="$(pwd)/_inst"
rm -rf "$prefix"
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
cmake --install build --prefix "$prefix"
echo "[pkg-config]"
PKG_CONFIG_PATH="$prefix/lib/pkgconfig:$prefix/lib64/pkgconfig" pkg-config --cflags --libs cosmoverse
echo "[CMake find_package]"
cat > test.cpp <<'CPP'
#include <cosmoverse/cosmoverse.hpp>
int main(){ return 0; }
CPP
cat > CMakeLists.txt <<'CML'
cmake_minimum_required(VERSION 3.20)
project(trycosmo CXX)
find_package(Cosmoverse REQUIRED)
add_executable(x test.cpp)
target_link_libraries(x PRIVATE Cosmoverse::cosmoverse)
CML
cmake -S . -B tbuild -DCMAKE_PREFIX_PATH="$prefix" && cmake --build tbuild -j
