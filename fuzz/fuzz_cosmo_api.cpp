
// SPDX-License-Identifier: Apache-2.0
#include <cstdint>
#include <cstddef>
#include <string>
#include "cosmoverse/c_api.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (!data || size == 0) return 0;
  // Example: feed bytes into a trivial API that should be robust
  cosmo_context* ctx = cosmo_create();
  if (!ctx) return 0;
  // Pretend we have a function that parses a buffer; if not present, just hash bytes
  size_t sum = 0; for (size_t i=0;i<size;i++) sum = (sum*131) ^ data[i];
  // Exercise a no-op API call if available
  cosmo_noop(ctx, (unsigned) (sum & 0xffffffffu));
  cosmo_destroy(ctx);
  return 0;
}
