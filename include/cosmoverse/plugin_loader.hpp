
// SPDX-License-Identifier: Apache-2.0
#pragma once
#include <string>
#include <vector>
namespace cosmoverse {
  struct PluginResult { int code; std::string name; };
  PluginResult run_plugin(const std::string& libpath, const std::vector<std::string>& args);
} // namespace cosmoverse
