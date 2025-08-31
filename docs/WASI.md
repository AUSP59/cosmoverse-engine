
# Building with WASI (wasi-sdk)
```bash
export WASI_SDK_PATH=/path/to/wasi-sdk
cmake -S . -B build-wasi -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/wasi.toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DCOSMO_BUILD_SHARED=OFF
cmake --build build-wasi -j
```
