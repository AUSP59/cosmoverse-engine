
# Building for Android
```bash
export ANDROID_NDK=/path/to/android-ndk
cmake -S . -B build-android -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/android.toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build build-android -j
```
