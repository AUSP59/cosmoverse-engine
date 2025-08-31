
// SPDX-License-Identifier: Apache-2.0
#pragma once
#if defined(_MSC_VER)
  #define COSMO_DEPRECATED(msg) __declspec(deprecated(msg))
#else
  #define COSMO_DEPRECATED(msg) __attribute__((deprecated(msg)))
#endif
