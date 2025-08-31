
# Sustainability & Green Engineering
- Prefer incremental, cached builds (ccache/sccache).
- Provide `COSMO_UNITY` and PCH to reduce CI energy per build.
- Avoid heavy runtime dependencies; default binaries are small and static options available.
- Offer opt-in for telemetry only with explicit consent (none by default).
