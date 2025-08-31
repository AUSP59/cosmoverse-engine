
# Native Packaging (Deb/RPM) via CPack
## Build
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
cpack -G DEB -B dist || true
cpack -G RPM -B dist || true
```
## Verify
```bash
dpkg-deb -I dist/*.deb || true
rpm -qpi dist/*.rpm || true
```
