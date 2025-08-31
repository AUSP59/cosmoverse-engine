
# Performance Tuning
- Build with **LTO**: `-DCOSMO_ENABLE_LTO=ON` (uses IPO if supported by the toolchain).
- Use release + hardening flags; consider `-march=native` for local builds (dont use in portable binaries).
- Check runtime features via `cosmoverse::cpu_summary()`.
- Use the **perf gate** and **Google Benchmark** harness for regression detection.


## Allocator selection
Choose alternative allocators at configure time:
```bash
cmake -S . -B build -DCOSMO_ALLOCATOR=mimalloc   # or jemalloc
```
