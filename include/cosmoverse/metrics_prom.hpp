
// SPDX-License-Identifier: Apache-2.0
#pragma once
#include <string>
#include <sstream>
#include <mutex>
#include <unordered_map>

namespace cosmoverse {
class MetricsRegistry {
  std::mutex m_;
  std::unordered_map<std::string,double> gauges_;
  std::unordered_map<std::string,double> counters_;
public:
  void inc(const std::string& name, double v=1.0){ std::lock_guard<std::mutex> lk(m_); counters_[name]+=v; }
  void set(const std::string& name, double v){ std::lock_guard<std::mutex> lk(m_); gauges_[name]=v; }
  std::string render() const {
    std::ostringstream o;
    for (auto& kv : counters_) o << "# TYPE " << kv.first << " counter\n" << kv.first << " " << kv.second << "\n";
    for (auto& kv : gauges_)   o << "# TYPE " << kv.first << " gauge\n"   << kv.first << " " << kv.second << "\n";
    return o.str();
  }
};
} // namespace cosmoverse
