
// SPDX-License-Identifier: Apache-2.0
#pragma once
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
namespace cosmoverse {
enum class LogLevel { trace=0, debug, info, warn, error, off };
class Logger {
  std::mutex m_;
  LogLevel lvl_ = LogLevel::info;
  bool json_ = false;
public:
  Logger(){
    if (const char* e = std::getenv("COSMO_LOG")) {
      std::string v(e);
      if (v=="trace") lvl_=LogLevel::trace; else if (v=="debug") lvl_=LogLevel::debug;
      else if (v=="info") lvl_=LogLevel::info; else if (v=="warn") lvl_=LogLevel::warn;
      else if (v=="error") lvl_=LogLevel::error; else if (v=="off") lvl_=LogLevel::off;
    }
    if (const char* j = std::getenv("COSMO_LOG_JSON")) json_ = std::string(j)=="1";
  }
  void log(LogLevel l, const std::string& msg){
    if (l < lvl_) return;
    auto now = std::chrono::system_clock::now();
    auto t = std::chrono::system_clock::to_time_t(now);
    std::ostringstream o;
    if (json_) {
      o << "{"ts":"" << std::put_time(std::gmtime(&t), "%FT%TZ") << "","level":"
        << (int)l << ","msg":"";
      for (char c: msg){ if (c=='"') o << "\\""; else if (c=='\n') o << "\\n"; else o << c; }
      o << ""}\n";
    } else {
      o << std::put_time(std::gmtime(&t), "%FT%TZ") << " [" << (int)l << "] " << msg << "\n";
    }
    std::lock_guard<std::mutex> lk(m_);
    std::cerr << o.str();
  }
};
inline Logger& logger(){ static Logger L; return L; }
inline void log_info(const std::string& m){ logger().log(LogLevel::info, m); }
inline void log_warn(const std::string& m){ logger().log(LogLevel::warn, m); }
inline void log_err(const std::string& m){ logger().log(LogLevel::error, m); }
} // namespace cosmoverse
