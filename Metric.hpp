#pragma once
#include "IMetric.hpp"
#include <iomanip>
#include <mutex>
#include <optional>
#include <sstream>

template <typename T> class Metric : public IMetric {
public:
  Metric(const std::string &name) : name_(name) {}

  void setValue(const T &value) {
    std::lock_guard<std::mutex> lock(mutex_);
    latestValue_ = value;
  }

  std::string
  toString(const std::chrono::system_clock::time_point &ts) const override {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!latestValue_.has_value())
      return "";

    auto time = std::chrono::system_clock::to_time_t(ts);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                  ts.time_since_epoch()) %
              1000;

    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&time));

    std::ostringstream oss;
    oss << buf << "." << std::setfill('0') << std::setw(3) << ms.count();
    oss << " \"" << name_ << "\" " << latestValue_.value();

    return oss.str();
  }

  void reset() override {
    std::lock_guard<std::mutex> lock(mutex_);
    latestValue_.reset();
  }

private:
  std::string name_;
  mutable std::mutex mutex_;
  std::optional<T> latestValue_;
};
