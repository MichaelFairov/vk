#pragma once
#include "IMetric.hpp"
#include "Metric.hpp"
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

class MetricsRegistry {
public:
  static MetricsRegistry &instance() {
    static MetricsRegistry inst;
    return inst;
  }

  template <typename T> void registerMetric(const std::string &name) {
    std::lock_guard<std::mutex> lock(mutex_);
    metrics_[name] = std::make_shared<Metric<T>>(name);
  }

  template <typename T> void record(const std::string &name, const T &value) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = metrics_.find(name);
    if (it != metrics_.end()) {
      auto typed = std::dynamic_pointer_cast<Metric<T>>(it->second);
      if (typed) {
        typed->setValue(value);
      }
    }
  }

  std::vector<std::shared_ptr<IMetric>> getAllMetrics() {
    std::lock_guard<std::mutex> lock(mutex_);
    std::vector<std::shared_ptr<IMetric>> copy;
    for (auto &[_, metric] : metrics_) {
      copy.push_back(metric);
    }
    return copy;
  }

private:
  std::unordered_map<std::string, std::shared_ptr<IMetric>> metrics_;
  std::mutex mutex_;
};
