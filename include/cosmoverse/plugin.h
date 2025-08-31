
// SPDX-License-Identifier: Apache-2.0
#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#if defined(_MSC_VER)
  #define COSMO_PLUGIN_EXPORT __declspec(dllexport)
#else
  #define COSMO_PLUGIN_EXPORT __attribute__((visibility("default")))
#endif

// Increment only on breaking changes.
#define COSMO_PLUGIN_ABI_VERSION 1

typedef struct cosmo_plugin_info {
  int abi_version;      // must equal COSMO_PLUGIN_ABI_VERSION
  const char* name;     // short, ASCII
} cosmo_plugin_info;

// Plugins must export BOTH symbols below:
COSMO_PLUGIN_EXPORT const cosmo_plugin_info* cosmoverse_plugin_info(void);
COSMO_PLUGIN_EXPORT int cosmoverse_plugin_run(int argc, const char** argv);

#ifdef __cplusplus
}
#endif
