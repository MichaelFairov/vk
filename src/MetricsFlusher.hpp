#pragma once
#include "MetricsRegistry.hpp"
#include <atomic>
#include <chrono>
#include <fstream>
#include <thread>

class MetricsFlusher {
public:
  MetricsFlusher(const std::string &filename, int interval_ms)
      : intervalMs_(interval_ms), running_(true),
        file_(filename, std::ios::app) {
    thread_ = std::thread([this]() {
      while (running_) {
        std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs_));
        flush();
      }
    });
  }

  ~MetricsFlusher() {
    running_ = false;
    if (thread_.joinable())
      thread_.join();
    flush(); // flush remaining metrics on shutdown
  }

private:
  void flush() {
    const auto now = std::chrono::system_clock::now();
    const auto metrics = MetricsRegistry::instance().getAllMetrics();

    for (const auto &metric : metrics) {
      const auto line = metric->toString(now);
      if (!line.empty()) {
        file_ << line << std::endl;
        metric->reset();
      }
    }
    file_.flush();
  }

  int intervalMs_;
  std::atomic<bool> running_;
  std::thread thread_;
  std::ofstream file_;
};
