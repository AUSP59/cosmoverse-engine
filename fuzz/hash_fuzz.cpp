
// SPDX-License-Identifier: Apache-2.0
#include "cosmoverse/hash.hpp"
#include <cstdint>
#include <cstddef>
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  (void)cosmoverse::fnv1a64(std::string_view(reinterpret_cast<const char*>(data), size));
  return 0;
}
