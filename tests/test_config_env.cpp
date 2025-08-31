
// SPDX-License-Identifier: Apache-2.0
#include "cosmoverse/config_env.hpp"
#include <cassert>
#include <fstream>
int main(){
  const char* path = "tmp_env.ini";
  std::ofstream o(path); o << "[s]\nk=v\n";
  setenv("COSMO_CONFIG", path, 1);
  cosmoverse::Config cfg; bool ok = cosmoverse::load_default_config(cfg);
  assert(ok); auto v = cfg.get("s.k"); assert(v && *v=="v");
  unsetenv("COSMO_CONFIG");
  std::remove(path);
  return 0;
}
