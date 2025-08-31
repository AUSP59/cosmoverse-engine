
// SPDX-License-Identifier: Apache-2.0
#include "cosmoverse/config_env.hpp"
#include <cstdlib>
#include <filesystem>
namespace fs = std::filesystem;
namespace cosmoverse {
static std::optional<fs::path> find_etc_relative() {
  fs::path p = fs::current_path() / "etc" / "cosmoverse.ini";
  if (fs::exists(p)) return p;
  return std::nullopt;
}
std::optional<std::string> default_config_path() {
  if (const char* c = std::getenv("COSMO_CONFIG")) {
    fs::path p(c); if (fs::exists(p)) return p.string();
  }
  if (const char* xdg = std::getenv("XDG_CONFIG_HOME")) {
    fs::path p(xdg); p /= "cosmoverse/cosmoverse.ini"; if (fs::exists(p)) return p.string();
  }
  if (const char* home = std::getenv("HOME")) {
    fs::path p(home); p /= ".config/cosmoverse/cosmoverse.ini"; if (fs::exists(p)) return p.string();
  }
  if (auto etc = find_etc_relative()) return etc->string();
  return std::nullopt;
}
bool load_default_config(Config& cfg) {
  auto p = default_config_path();
  return p ? cfg.load_file(*p) : false;
}
} // namespace cosmoverse
