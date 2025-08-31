
// SPDX-License-Identifier: Apache-2.0
#pragma once
#include <cstdint>
namespace cosmoverse {
struct CpuCaps {
  bool sse2=false, avx2=false, neon=false;
};
CpuCaps detect_cpu_caps();
using Kernel = void(*)(uint8_t*, const uint8_t*, size_t);
struct Dispatch {
  Kernel generic=nullptr, sse2=nullptr, avx2=nullptr, neon=nullptr;
  Kernel pick(const CpuCaps& c) const {
    if (c.avx2 && avx2) return avx2;
    if (c.sse2 && sse2) return sse2;
    if (c.neon && neon) return neon;
    return generic;
  }
};
} // namespace cosmoverse
