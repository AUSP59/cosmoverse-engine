
# Observability
- Logging via `COSMO_LOG` env (`trace|debug|info|warn|error|off`).
- Optional OpenTelemetry spans: build with `-DCOSMO_ENABLE_OTEL=ON` (if SDK headers exist).
- Prometheus text-format helper `cosmoverse::MetricsRegistry` (header-only) for counters/gauges.
