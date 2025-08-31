
// SPDX-License-Identifier: Apache-2.0
#pragma once
// Lightweight OTEL wrapper; compiled only if the SDK is available.
#if __has_include(<opentelemetry/trace/provider.h>)
  #define COSMO_HAVE_OTEL 1
  #include <opentelemetry/trace/provider.h>
  namespace cosmoverse { namespace otel {
    inline auto tracer() {
      return opentelemetry::trace::Provider::GetTracerProvider()->GetTracer("cosmoverse");
    }
    struct Span {
      std::unique_ptr<opentelemetry::trace::Span> s;
      explicit Span(const char* name)
        : s(tracer()->StartSpan(name)) {}
      ~Span(){ s->End(); }
    };
  }}
#else
  #define COSMO_HAVE_OTEL 0
  namespace cosmoverse { namespace otel {
    struct Span { explicit Span(const char*){} };
  }}
#endif
