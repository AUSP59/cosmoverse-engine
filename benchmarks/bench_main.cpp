// SPDX-License-Identifier: Apache-2.0

#include "cosmoverse/thread_pool.hpp"
#include <chrono>
#include <future>
#include <iostream>
#include <vector>

int main() {
  using namespace std::chrono;
  const int tasks = 200000;
  cosmoverse::ThreadPool pool;
  std::vector<std::future<int>> futs; futs.reserve(tasks);
  auto t0 = high_resolution_clock::now();
  for (int i=0;i<tasks;++i) futs.emplace_back(pool.submit([i]{ return i*i; }));
  long long sum=0; for (auto& f : futs) sum += f.get();
  auto t1 = high_resolution_clock::now();
  auto ms = duration_cast<milliseconds>(t1 - t0).count();
  std::cout << "Ran " << tasks << " tasks in " << ms << " ms; sum=" << sum << "\n";
  return 0;
}
