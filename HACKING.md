
# HACKING
- Use `CMakePresets.json` to configure common builds.
- Run `pre-commit run -a` before pushing.
- Prefer `clang` + `lld` locally for speed (`-DCOSMO_USE_LLD=ON`).
