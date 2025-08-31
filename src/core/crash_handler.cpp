
// SPDX-License-Identifier: Apache-2.0
#include <csignal>
#include <cstdio>
#if defined(__unix__) || defined(__APPLE__)
#  include <execinfo.h>
#  include <unistd.h>
#endif
namespace cosmoverse {
static void cosmo_signal_handler(int sig){
  std::fprintf(stderr, "COSMOVERSE: fatal signal %d\n", sig);
#if defined(__unix__) || defined(__APPLE__)
  void* bt[32];
  int n = backtrace(bt, 32);
  backtrace_symbols_fd(bt, n, STDERR_FILENO);
#endif
  std::_Exit(128 + sig);
}
struct CrashInstall {
  CrashInstall(){
#if defined(COSMO_CRASH_HANDLER) && (defined(__unix__) || defined(__APPLE__))
    std::signal(SIGSEGV, cosmo_signal_handler);
    std::signal(SIGABRT, cosmo_signal_handler);
#endif
  }
} _cosmo_crash_install;
} // namespace cosmoverse
