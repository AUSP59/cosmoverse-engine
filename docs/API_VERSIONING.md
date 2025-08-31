
# API Versioning Policy
- Semantic versioning MAJOR.MINOR.PATCH.
- **C API**: ABI preserved across MINOR; breaking changes only on MAJOR.
- Deprecated APIs remain for ≥2 MINOR releases and are marked with `COSMO_DEPRECATED` macro.
