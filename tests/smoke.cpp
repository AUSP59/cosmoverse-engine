
// SPDX-License-Identifier: Apache-2.0
#include <cassert>
#include <string>
#include "cosmoverse/engine.hpp"
int main() {
  auto v = cosmoverse::version();
  assert(!v.empty());
  auto g = cosmoverse::greet("World");
  if (g != std::string("Hello, World!")) return 2;
  return 0;
}
