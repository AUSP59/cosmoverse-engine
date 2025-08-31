
# API Stability Policy
- We follow SemVer. Public C++ APIs are versioned and changes are gated by ABI checks.
- Breaking changes are only allowed in major releases and must be documented with migration notes.
- Deprecated APIs use `COSMO_DEPRECATED("message")` and exist for at least one minor release before removal.
