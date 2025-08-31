// SPDX-License-Identifier: Apache-2.0

#pragma once
#include <cctype>
#include <fstream>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>

namespace cosmoverse {

class Config {
 public:
  bool load_file(const std::string& path) {
    std::ifstream in(path);
    if (!in) return false;
    std::string line, section;
    while (std::getline(in, line)) {
      if (line.empty() || line[0] == '#') continue;
      if (line.front() == '[' && line.back() == ']') { section = line.substr(1, line.size()-2); continue; }
      auto pos = line.find('=');
      if (pos == std::string::npos) continue;
      auto key = trim(line.substr(0, pos));
      auto val = trim(line.substr(pos+1));
      std::string full = section.empty() ? key : section + "." + key;
      kv_[full] = val;
    }
    return true;
  }

  std::optional<std::string> get(std::string_view key) const {
    auto it = kv_.find(std::string(key));
    if (it == kv_.end()) return std::nullopt;
    return it->second;
  }

 private:
  static std::string trim(std::string s) {
    auto issp = [](unsigned char c){ return std::isspace(c); };
    while (!s.empty() && issp(s.front())) s.erase(s.begin());
    while (!s.empty() && issp(s.back())) s.pop_back();
    return s;
  }

  std::unordered_map<std::string, std::string> kv_;
};

}  // namespace cosmoverse
