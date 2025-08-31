
// SPDX-License-Identifier: Apache-2.0
#pragma once
#include <string>
#include <string_view>
namespace cosmoverse {
inline std::string version() { return "1.0.0"; }
inline std::string greet(std::string_view name) { return std::string("Hello, ") + std::string(name) + "!"; }
} // namespace cosmoverse
