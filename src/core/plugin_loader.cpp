
// SPDX-License-Identifier: Apache-2.0
#include "cosmoverse/plugin_loader.hpp"
#include "cosmoverse/plugin.h"
#include <stdexcept>
#include <cstring>
#include <fstream>
#include <algorithm>
#if defined(_WIN32)
  #include <windows.h>
#else
  #include <dlfcn.h>
#endif

namespace cosmoverse {
static void* open_lib(const char* p){
#if defined(_WIN32)
  return (void*)LoadLibraryA(p);
#else
  return dlopen(p, RTLD_NOW);
#endif
}
static void* get_sym(void* h, const char* s){
#if defined(_WIN32)
  return (void*)GetProcAddress((HMODULE)h, s);
#else
  return dlsym(h, s);
#endif
}
static std::string last_error(){
#if defined(_WIN32)
  DWORD e = GetLastError(); char buf[256];
  FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,0,e,0,buf,sizeof(buf),0);
  return std::string(buf);
#else
  const char* e = dlerror(); return e? std::string(e): std::string();
#endif
}

PluginResult run_plugin(const std::string& libpath, const std::vector<std::string>& args){
  void* h = open_lib(libpath.c_str());
  if (!h) throw std::runtime_error(std::string("Failed to open plugin: ")+last_error());
  auto info_fn = (const cosmo_plugin_info* (*)()) get_sym(h, "cosmoverse_plugin_info");
  auto run_fn  = (int (*)(int,const char**)) get_sym(h, "cosmoverse_plugin_run");
  if (!info_fn || !run_fn) throw std::runtime_error("Missing required symbols in plugin");
  const cosmo_plugin_info* info = info_fn();
  if (!info || info->abi_version != COSMO_PLUGIN_ABI_VERSION) throw std::runtime_error("ABI mismatch");
  std::vector<const char*> cargs; cargs.reserve(args.size());
  for (auto& s: args) cargs.push_back(s.c_str());
  
// Allowlist check (if configured)
const char* allow = std::getenv("COSMO_PLUGIN_ALLOWLIST_FILE");
if (allow){
  std::string h;
  if (!sha256_of_file(libpath, h)) throw std::runtime_error("OpenSSL missing for SHA-256 or unreadable plugin file");
  if (!is_hash_allowed(allow, h)) throw std::runtime_error(std::string("Plugin SHA-256 not in allowlist: ")+h);
}
int rc = run_fn((int)cargs.size(), cargs.data());

  return { rc, info->name? std::string(info->name): std::string() };
}
} // namespace cosmoverse
