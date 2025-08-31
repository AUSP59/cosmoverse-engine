
// SPDX-License-Identifier: Apache-2.0
#include "cosmoverse/log.hpp"
#include <cstdlib>
namespace cosmoverse {
struct LogEnvInit {
  LogEnvInit() {
    const char* lvl = std::getenv("COSMO_LOG_LEVEL");
    if (!lvl) return;
    std::string s(lvl);
    for (auto& c: s) c = (char)tolower(c);
    LogLevel L = LogLevel::Info;
    if (s=="trace") L = LogLevel::Trace;
    else if (s=="debug") L = LogLevel::Debug;
    else if (s=="info") L = LogLevel::Info;
    else if (s=="warn" || s=="warning") L = LogLevel::Warn;
    else if (s=="error") L = LogLevel::Error;
    logger().set_level(L);
  }
} _log_env_init;
} // namespace cosmoverse
