
set(CMAKE_SYSTEM_NAME WASI)
set(CMAKE_SYSTEM_PROCESSOR wasm32)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_FLAGS "--target=wasm32-wasi")
set(CMAKE_CXX_FLAGS "--target=wasm32-wasi")
set(CMAKE_EXE_LINKER_FLAGS "--target=wasm32-wasi")
