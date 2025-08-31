
// SPDX-License-Identifier: Apache-2.0
#pragma once
#include <cstdlib>
#include "cosmoverse/logging.hpp"

namespace cosmoverse {
inline void install_crash_handlers();
}

#if defined(_WIN32)
  #include <windows.h>
  static long __stdcall cosmo_unhandled(EXCEPTION_POINTERS*){
    cosmoverse::log(cosmoverse::LogLevel::error, "Unhandled exception");
    return EXCEPTION_EXECUTE_HANDLER;
  }
#elif defined(__unix__) || defined(__APPLE__)
  #include <signal.h>
  #include <execinfo.h>
  #include <unistd.h>
  static void cosmo_sig(int sig){
    void* bt[32]; int n=backtrace(bt,32);
    cosmoverse::log(cosmoverse::LogLevel::error, "Signal %d received. Backtrace frames=%d", sig, n);
    backtrace_symbols_fd(bt,n, STDERR_FILENO);
    _exit(128+sig);
  }
#endif

namespace cosmoverse {
inline void install_crash_handlers(){
#if defined(_WIN32)
  SetUnhandledExceptionFilter(cosmo_unhandled);
#else
  signal(SIGSEGV, cosmo_sig);
  signal(SIGABRT, cosmo_sig);
#endif
}
}

// Run at load (constructor) to install handlers if enabled
#if defined(_MSC_VER)
  #pragma section(".CRT$XCU",read)
  extern "C" __declspec(allocate(".CRT$XCU")) void (*cosmo_ctor)(void) = [](){ 
    if (std::getenv("COSMO_CRASH_HANDLER") && std::string(std::getenv("COSMO_CRASH_HANDLER"))=="0") return;
    cosmoverse::install_crash_handlers(); 
  };
#else
  __attribute__((constructor)) static void cosmo_ctor(){
    const char* v = std::getenv("COSMO_CRASH_HANDLER");
    if (v && std::string(v)=="0") return;
    cosmoverse::install_crash_handlers();
  }
#endif
