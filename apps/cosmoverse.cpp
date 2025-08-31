// SPDX-License-Identifier: Apache-2.0

#include "cosmoverse/cosmoverse.hpp"
#include "cosmoverse/i18n.hpp"
#include "cosmoverse/build_info.hpp"
#include "cosmoverse/config.hpp"
#include "cosmoverse/hash.hpp"
#include "cosmoverse/log.hpp"
#include "cosmoverse/thread_pool.hpp"

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace cosmoverse;

static void help() {
  std::cout << "COSMOVERSE ENGINE CLI (" << version() << ")\n"
            << "Usage: cosmoverse <command> [args]\n\n"
            << ""+cosmo_gettext("Commands:\n"
            << "  plugin-sandbox <path> [args]  Run plugin in a separate process\n")+"
            << "  plugin <path> [args]     Load and run a plugin\n"
            << "  bench-omp <tasks>        Run OpenMP micro-bench (if enabled)\n"
            << "  doctor                   Run environment checks\\n"
            << "  gen-config <path>        Write default config\\n"
            << "  version                  Print version\n"
            << "  wc <file>                Count lines, words, bytes\n"
            << "  hash <file>              FNV1a-64 hash of file\n"
            << "  bench [tasks=100000] [threads]   Run thread-pool micro-benchmark\n"
            << "  help                     Show help\n";
}

static uint64_t hash_file(const std::filesystem::path& p) {
  std::ifstream in(p, std::ios::binary);
  if (!in) throw std::runtime_error("Cannot open file");
  const uint64_t FNV_OFFSET = 1469598103934665603ull;
  const uint64_t FNV_PRIME  = 1099511628211ull;
  uint64_t h = FNV_OFFSET;
  char buf[4096];
  while (in.read(buf, sizeof(buf)) || in.gcount() > 0) {
    std::size_t n = static_cast<std::size_t>(in.gcount());
    for (std::size_t i = 0; i < n; ++i) { h ^= static_cast<unsigned char>(buf[i]); h *= FNV_PRIME; }
  }
  return h;
}

static void wc_file(const std::filesystem::path& p) {
  std::ifstream in(p, std::ios::binary);
  if (!in) throw std::runtime_error("Cannot open file");
  std::size_t lines=0, words=0, bytes=0;
  bool in_word=false;
  char c;
  while (in.get(c)) {
    ++bytes;
    if (c == '\n') ++lines;
    if (std::isspace(static_cast<unsigned char>(c))) {
      in_word=false;
    } else if (!in_word) {
      in_word=true; ++words;
    }
  }
  std::cout << lines << " " << words << " " << bytes << " " << p.string() << "\n";
}


static int write_default_config(const std::filesystem::path& p) {
  std::ofstream o(p);
  if (!o) return 2;
  o << "# COSMOVERSE default configuration\n";
  o << "[log]\nlevel=info\n";
  o << "[bench]\ntasks=100000\nthreads=0\n";
  return 0;
}
static void doctor() {
  std::cout << "Checking environment...\n";
  std::cout << "Threads: " << std::thread::hardware_concurrency() << "\n";
  std::cout << "Cosmoverse version: " << version() << "\n";
}

int main(int argc, char** argv) {
  logger().set_level(LogLevel::Info);
  if (argc < 2) { help(); return 0; }
  std::string cmd = argv[1];
  try {
    if (cmd == "version") {
      std::cout << version() << "\n";
    } else if (cmd == "help" || cmd == "--help" || cmd == "-h") {
      help();
    } else if (cmd == "doctor") { doctor(); } else if (cmd == "gen-config") { if (argc<3){std::cerr<<"Missing <path>\\n"; return 2;} return write_default_config(argv[2]); } else if (cmd == "wc") {
      if (argc < 3) { std::cerr << "Missing <file>\n"; return 2; }
      wc_file(argv[2]);
    } else if (cmd == "hash") {
      if (argc < 3) { std::cerr << "Missing <file>\n"; return 2; }
      std::cout << std::hex << hash_file(argv[2]) << std::dec << "\n";
    
    } else if (cmd == "bench-omp") {
#ifdef _OPENMP
      long tasks = (argc>=3)? std::stol(argv[2]) : 200000;
      auto t0 = std::chrono::steady_clock::now();
      long long sum = 0;
#pragma omp parallel for reduction(+:sum)
      for (long i=0;i<tasks;++i) sum += i*i;
      auto t1 = std::chrono::steady_clock::now();
      auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
      if(flag_json){ std::cout << "{\"tasks\":"<<tasks<<",\"checksum\":"<<sum<<",\"ms\":"<<ms<<"}\n"; }
      else { std::cout << "Computed " << tasks << " tasks in " << ms << " ms (OpenMP), checksum=" << sum << "\n"; }
#else
      std::cerr << "OpenMP not enabled. Rebuild with -DCOSMO_ENABLE_OPENMP=ON\n";
      return 2;
#endif
    
} else if (cmd == "plugin") {
  if (argc < 3) { std::cerr << "Usage: cosmoverse plugin <path> [args...]\n"; return 2; }
  std::string lib = argv[2];
  std::vector<std::string> pargs;
  for (int i=3;i<argc;++i) pargs.emplace_back(argv[i]);
  try {
    auto res = cosmoverse::run_plugin(lib, pargs);
    if (flag_json) {
      std::cout << "{\"plugin\":\"" << res.name << "\",\"code\":" << res.code << "}\n";
    } else {
      std::cout << "plugin '" << res.name << "' exited with code " << res.code << "\n";
    }
    return res.code;
  } catch (const std::exception& e) {
    if (flag_json) { std::cout << "{\"error\":\"" << e.what() << "\"}\n"; }
    else { std::cerr << "Error: " << e.what() << "\n"; }
    return 3;
  }

    
        } else if (cmd == "plugin-sandbox") {
          if (argc < 3) { std::cerr << "Usage: cosmoverse plugin-sandbox <path> [args...]\n"; return 2; }
          std::string runner = "cosmo_plugin_runner";
          // Try to find runner next to this binary
          try {
            std::string quoted;
#if defined(_WIN32)
            quoted = "\"" + runner + "\"";
            std::string cmdline = quoted + " \"" + std::string(argv[2]) + "\"";
            for (int i=3;i<argc;++i){ cmdline += " \"" + std::string(argv[i]) + "\""; }
            int rc = system(cmdline.c_str());
            return rc;
#else
            quoted = runner;
            std::string cmdline = quoted + " \"" + std::string(argv[2]) + "\"";
            for (int i=3;i<argc;++i){ cmdline += " \"" + std::string(argv[i]) + "\""; }
            int rc = system(cmdline.c_str());
            if (WIFEXITED(rc)) return WEXITSTATUS(rc);
            return 3;
#endif
          } catch(...) { return 3; }

    } else if (cmd == "bench") {

      int tasks = (argc >= 3) ? std::stoi(argv[2]) : 100000;
      int threads = (argc>=4)? std::stoi(argv[3]) : (int)std::thread::hardware_concurrency(); if(threads<=0) threads=(int)std::thread::hardware_concurrency(); ThreadPool pool((std::size_t)threads);
      std::vector<std::future<int>> futs; futs.reserve(tasks);
      for (int i=0;i<tasks;++i) futs.emplace_back(pool.submit([i]{ return i*i; }));
      long long sum = 0; for (auto& f: futs) sum += f.get();
      std::cout << "Computed " << tasks << " tasks, checksum=" << sum << "\n";
    } else {
      std::cerr << "Unknown command: " << cmd << "\n"; help(); return 2;
    }
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
  return 0;
}
