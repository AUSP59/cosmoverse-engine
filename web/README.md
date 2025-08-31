
# WebAssembly Demo (Emscripten)

Build the library for wasm and a tiny demo:

```bash
docker run --rm -it -v $PWD:/src -w /src emscripten/emsdk:3.1.60 bash -lc '
  emcmake cmake -S . -B build-wasm -DCMAKE_BUILD_TYPE=Release -DCOSMO_BUILD_SHARED=OFF -DCOSMO_BUILD_TESTS=OFF &&
  cmake --build build-wasm -j &&
  emcc apps/wasm_demo.c build-wasm/libcosmoverse.a -Iinclude -o web/cosmoverse.html
'
```

Open `web/cosmoverse.html` in a browser.
