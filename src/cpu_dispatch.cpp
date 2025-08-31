
// SPDX-License-Identifier: Apache-2.0
#include "cosmoverse/cpu_dispatch.hpp"
#if defined(_MSC_VER)
  #include <intrin.h>
#elif defined(__x86_64__) || defined(__i386__)
  #include <cpuid.h>
#endif
namespace cosmoverse {
CpuCaps detect_cpu_caps(){
  CpuCaps r{};
#if defined(__x86_64__) || defined(_M_X64) || defined(__i386__) || defined(_M_IX86)
  unsigned int eax,ebx,ecx,edx;
  #if defined(_MSC_VER)
    int regs[4]; __cpuidex(regs, 1, 0);
    edx = regs[3]; ecx = regs[2];
    __cpuidex(regs, 7, 0);
    ebx = regs[1];
  #else
    __cpuid_count(1,0,eax,ebx,ecx,edx);
    unsigned int a2,b2,c2,d2; __cpuid_count(7,0,a2,b2,c2,d2);
    ebx = b2;
  #endif
  r.sse2 = (edx & (1u<<26)) != 0;
  r.avx2 = (ebx & (1u<<5))  != 0;
#elif defined(__aarch64__) || defined(__ARM_NEON)
  r.neon = true;
#endif
  return r;
}
} // namespace cosmoverse
