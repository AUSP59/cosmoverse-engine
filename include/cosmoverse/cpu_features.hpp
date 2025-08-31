
// SPDX-License-Identifier: Apache-2.0
#pragma once
#include <string>
namespace cosmoverse {
inline bool cpu_has_avx2() {
#if defined(__x86_64__) || defined(_M_X64) || defined(__i386) || defined(_M_IX86)
  #if defined(__GNUC__) || defined(__clang__)
    return __builtin_cpu_supports("avx2");
  #else
    return false;
  #endif
#else
  return false;
#endif
}
inline std::string cpu_summary() {
  return std::string("avx2=") + (cpu_has_avx2() ? "1":"0");
}
} // namespace cosmoverse
