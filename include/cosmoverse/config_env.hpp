
// SPDX-License-Identifier: Apache-2.0
#pragma once
#include "cosmoverse/config.hpp"
#include <optional>
#include <string>
namespace cosmoverse {
  // Resolve a default config path using: COSMO_CONFIG, XDG_CONFIG_HOME, HOME/.config, or etc/cosmoverse.ini
  std::optional<std::string> default_config_path();
  // Load config from the resolved default path (returns false if not found).
  bool load_default_config(Config& cfg);
} // namespace cosmoverse
