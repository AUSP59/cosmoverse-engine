
// SPDX-License-Identifier: Apache-2.0
#pragma once
// Minimal macro surface: if COSMO_ENABLE_OTEL and headers exist, emit spans; otherwise no-op.
#if defined(COSMO_ENABLE_OTEL) && __has_include(<opentelemetry/trace/provider.h>)
  #include <opentelemetry/trace/provider.h>
  #define COSMO_SPAN(name) auto _cosmo_span = opentelemetry::trace::Provider::GetTracer("cosmoverse")->StartSpan(name); auto _cosmo_scope = opentelemetry::trace::Scope(_cosmo_span);
#else
  #define COSMO_SPAN(name) (void)0
#endif
