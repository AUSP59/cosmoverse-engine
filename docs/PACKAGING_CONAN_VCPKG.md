
# Packaging via Conan and vcpkg
## Conan (v2)
```bash
conan profile detect
conan create . --build=missing
```
## vcpkg (port example)
- See `vcpkg.json` and `ports/cosmoverse/portfile.cmake` (update URL/REF for your repo).
