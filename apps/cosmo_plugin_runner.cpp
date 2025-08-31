
// SPDX-License-Identifier: Apache-2.0
#include "cosmoverse/plugin_loader.hpp"
#include <iostream>
int main(int argc, char** argv){
  if (argc < 2){ std::cerr << "usage: cosmo_plugin_runner <plugin> [args...]\n"; return 2; }
  std::string lib = argv[1];
  std::vector<std::string> args;
  for (int i=2;i<argc;++i) args.emplace_back(argv[i]);
  try{
    auto res = cosmoverse::run_plugin(lib, args);
    std::cout << "plugin '"<<res.name<<"' exited with code "<<res.code<<"\n";
    return res.code;
  }catch(const std::exception& e){
    std::cerr << "Error: " << e.what() << "\n";
    return 3;
  }
}
