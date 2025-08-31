
// SPDX-License-Identifier: Apache-2.0
#pragma once
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <ctime>

namespace cosmoverse {
enum class LogLevel { trace=0, debug=1, info=2, warn=3, error=4, off=5 };

inline LogLevel parse_level(const char* s){
  if(!s) return LogLevel::info;
  #define CMP(x) if(std::strcmp(s, x)==0) return LogLevel::x;
  CMP("trace") CMP("debug") CMP("info") CMP("warn") CMP("error") CMP("off")
  #undef CMP
  return LogLevel::info;
}

inline LogLevel& global_level(){ static LogLevel L = parse_level(std::getenv("COSMO_LOG")); return L; }

inline void log(LogLevel lvl, const char* fmt, ...){
  if((int)lvl < (int)global_level()) return;
  const char* names[]={"TRACE","DEBUG","INFO","WARN","ERROR"};
  std::time_t t=std::time(nullptr); std::tm tm{};
#if defined(_WIN32)
  localtime_s(&tm, &t);
#else
  localtime_r(&t, &tm);
#endif
  char ts[32]; std::strftime(ts,sizeof(ts),"%Y-%m-%d %H:%M:%S",&tm);
  std::fprintf(stderr,"[%s] %s ", ts, names[(int)lvl]);
  va_list ap; va_start(ap, fmt); std::vfprintf(stderr, fmt, ap); va_end(ap);
  std::fprintf(stderr,"
");
}
} // namespace cosmoverse
