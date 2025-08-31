
// SPDX-License-Identifier: Apache-2.0
#include <iostream>
#include "cosmoverse/engine.hpp"
int main(int argc, char** argv){
  std::string who = (argc>1)? argv[1] : "Cosmoverse";
  std::cout << cosmoverse::greet(who) << "\n";
  return 0;
}
