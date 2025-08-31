// SPDX-License-Identifier: Apache-2.0

#include "cosmoverse/cosmoverse.hpp"
#include "cosmoverse/hash.hpp"
#include "cosmoverse/thread_pool.hpp"
#include <cassert>
#include <string>

int main() {
  // version exists
  assert(!cosmoverse::version().empty());
  // hash determinism
  auto h1 = cosmoverse::fnv1a64("abc");
  auto h2 = cosmoverse::fnv1a64(std::string("abc"));
  assert(h1 == h2);
  // thread pool returns value
  cosmoverse::ThreadPool pool(2);
  auto f = pool.submit([]{ return 7*6; });
  assert(f.get() == 42);
  return 0;
}
