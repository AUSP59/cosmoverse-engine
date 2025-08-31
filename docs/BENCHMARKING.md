
# Benchmarking Methodology
- Pin CPU governor to `performance` if possible; disable turbo/power drift for consistent runs.
- Use `cosmoverse bench` for smoke and Google Benchmark harness (`-DCOSMO_ENABLE_BENCHMARKS=ON`) for in-depth.
- Report bytes processed and runtime in ms; collect at least 5 runs.
