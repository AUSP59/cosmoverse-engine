
// SPDX-License-Identifier: Apache-2.0
#pragma once
#if defined _WIN32 || defined __CYGWIN__
  #if defined(COSMOVERSE_BUILD_SHARED)
    #define COSMO_API __declspec(dllexport)
  #elif defined(COSMOVERSE_USE_SHARED)
    #define COSMO_API __declspec(dllimport)
  #else
    #define COSMO_API
  #endif
#else
  #if __GNUC__ >= 4
    #define COSMO_API __attribute__((visibility("default")))
  #else
    #define COSMO_API
  #endif
#endif
