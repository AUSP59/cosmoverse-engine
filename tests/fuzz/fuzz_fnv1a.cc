
// SPDX-License-Identifier: Apache-2.0
#include <cstdint>
#include <cstddef>
#include "cosmoverse/c_api.h"
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  (void)cosmoverse_fnv1a64_c(reinterpret_cast<const signed char*>(Data), (int)Size);
  return 0;
}
