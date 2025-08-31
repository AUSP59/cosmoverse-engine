
// SPDX-License-Identifier: Apache-2.0
#include "cosmoverse/hash.hpp"
#include <fstream>
#include <iostream>
#include <vector>
int main(int argc, char** argv){
  if(argc<2){ std::cerr<<"usage: hash_file <path>\n"; return 2; }
  std::ifstream in(argv[1], std::ios::binary); if(!in){ std::cerr<<"cannot open\n"; return 1; }
  std::vector<char> buf((std::istreambuf_iterator<char>(in)),{});
  std::cout << std::hex << cosmoverse::fnv1a64({buf.data(), buf.size()}) << "\n";
  return 0;
}
