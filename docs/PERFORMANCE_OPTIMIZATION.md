
# Performance Optimization Playbook
- **IPO/LTO**: `-DCOSMO_IPO=ON` (requires supported toolchain).
- **Unity builds**: `-DCOSMO_UNITY_BUILD=ON` to speed up compilation.
- **PGO**: run `scripts/pgo_bootstrap.sh` to generate & use profiles.
- **BOLT/AutoFDO** (advisory): record profiles with `perf` on Linux and apply with `llvm-bolt` when available.
- **Hyperfine**: see CI workflow for historical CLI timing.
