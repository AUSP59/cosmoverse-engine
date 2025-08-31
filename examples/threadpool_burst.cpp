
// SPDX-License-Identifier: Apache-2.0
#include "cosmoverse/thread_pool.hpp"
#include <iostream>
#include <future>
#include <vector>
int main(){
  cosmoverse::ThreadPool pool;
  std::vector<std::future<int>> futs;
  for(int i=0;i<1000;++i) futs.emplace_back(pool.submit([i]{ return i*i; }));
  long long sum=0; for(auto& f: futs) sum += f.get();
  std::cout << "sum=" << sum << "\n";
  return 0;
}
