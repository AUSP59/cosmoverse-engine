// SPDX-License-Identifier: Apache-2.0
#pragma once
#include <string_view>
namespace cosmoverse {

COSMO_API inline constexpr std::string_view version() noexcept { return COSMO_VERSION; }

}  // namespace cosmoverse
