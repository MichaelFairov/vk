#pragma once
#include <chrono>
#include <string>

class IMetric {
public:
  virtual ~IMetric() = default;

  virtual std::string
  toString(const std::chrono::system_clock::time_point &ts) const = 0;
  virtual void reset() = 0;
};
