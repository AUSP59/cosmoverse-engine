
# Mobile builds
## Android (NDK)
```bash
export ANDROID_NDK_HOME=/path/to/android-ndk
cmake -S . -B build-android -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/android.toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build build-android -j
```

## iOS (Xcode toolchain)
```bash
cmake -S . -B build-ios -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/ios.toolchain.cmake -G Xcode
cmake --build build-ios --config Release
```
