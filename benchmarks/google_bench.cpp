
// SPDX-License-Identifier: Apache-2.0
#include <benchmark/benchmark.h>
#include "cosmoverse/c_api.h"
#include <string>
static void BM_FNV1a64(benchmark::State& st){
  std::string s(st.range(0), 'a');
  for (auto _ : st){
    (void)cosmoverse_fnv1a64_c(reinterpret_cast<const signed char*>(s.data()), s.size());
  }
  st.SetBytesProcessed(int64_t(st.iterations()) * st.range(0));
}
BENCHMARK(BM_FNV1a64)->Arg(64)->Arg(256)->Arg(1024);
BENCHMARK_MAIN();
