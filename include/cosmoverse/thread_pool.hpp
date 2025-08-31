// SPDX-License-Identifier: Apache-2.0

#pragma once
#include <atomic>
#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include "cosmoverse/export.hpp"

namespace cosmoverse {

class COSMO_API ThreadPool {
 public:
  explicit ThreadPool(std::size_t n = std::thread::hardware_concurrency()) : stop_(false) {
    if (n == 0) n = 1;
    for (std::size_t i = 0; i < n; ++i) { workers_.emplace_back([this]{ worker(); }); }
  }
  ~ThreadPool() { shutdown(); }

  template <typename F, typename... Args>
  auto submit(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>> {
    using R = std::invoke_result_t<F, Args...>;
    auto task = std::packaged_task<R()>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    auto fut = task.get_future();
    { std::lock_guard<std::mutex> lk(mu_); tasks_.emplace([t = std::move(task)]() mutable { t(); }); }
    cv_.notify_one();
    return fut;
  }

  void shutdown() {
    bool expected = false;
    if (!stop_.compare_exchange_strong(expected, true)) return;
    cv_.notify_all();
    for (auto& t : workers_) if (t.joinable()) t.join();
  }

 private:
  void worker() {
    for (;;) {
      std::function<void()> job;
      {
        std::unique_lock<std::mutex> lk(mu_);
        cv_.wait(lk, [&]{ return stop_ || !tasks_.empty(); });
        if (stop_ && tasks_.empty()) return;
        job = std::move(tasks_.front()); tasks_.pop();
      }
      job();
    }
  }

  std::vector<std::thread> workers_;
  std::queue<std::function<void()>> tasks_;
  std::mutex mu_;
  std::condition_variable cv_;
  std::atomic<bool> stop_;
};

}  // namespace cosmoverse
