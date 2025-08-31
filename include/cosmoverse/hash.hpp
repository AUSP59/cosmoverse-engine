// SPDX-License-Identifier: Apache-2.0

#pragma once
#include <cstdint>
#include <string_view>

namespace cosmoverse {
// FNV-1a 64-bit
inline uint64_t fnv1a64(std::string_view s) {
  const uint64_t FNV_OFFSET = 1469598103934665603ull;
  const uint64_t FNV_PRIME  = 1099511628211ull;
  uint64_t hash = FNV_OFFSET;
  for (unsigned char c : s) { hash ^= c; hash *= FNV_PRIME; }
  return hash;
}
} // namespace cosmoverse
