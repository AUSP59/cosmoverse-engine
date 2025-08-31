
# Plugin System
- **ABI**: C ABI (`include/cosmoverse/plugin.h`), `COSMO_PLUGIN_ABI_VERSION=1`.
- **Exports**: `cosmoverse_plugin_info()` and `cosmoverse_plugin_run(argc, argv)`.
- **CLI**: `cosmoverse plugin <path> [args...]` loads the .so/.dylib/.dll and executes it.
- **Security**: Treat plugins as untrusted code. Consider containerization (`--security-opt seccomp=...`) and only load signed plugins.


## Allowlist (optional, sha256)
To restrict which plugins can run, set `COSMO_PLUGIN_ALLOWLIST_FILE=/path/allowlist.txt` where each line contains a lowercase SHA-256 of an approved plugin file. Build with OpenSSL available to enable hashing; otherwise the check is disabled at runtime.
