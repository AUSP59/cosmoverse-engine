
// SPDX-License-Identifier: Apache-2.0
#include "cosmoverse/plugin.h"
#include <cstdio>
static cosmo_plugin_info INFO{ COSMO_PLUGIN_ABI_VERSION, "sample" };
extern "C" const cosmo_plugin_info* cosmoverse_plugin_info(void){ return &INFO; }
extern "C" int cosmoverse_plugin_run(int argc, const char** argv){
  std::printf("COSMOVERSE sample plugin running with %d args\n", argc);
  for (int i=0;i<argc;++i) std::printf("arg[%d]=%s\n", i, argv[i]);
  return argc % 2; // deterministic non-zero sometimes for demo
}
