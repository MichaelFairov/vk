#include "src/MetricsFlusher.hpp"
#include <cstdint>

int main() {
  auto &registry = MetricsRegistry::instance();

  registry.registerMetric<double>("CPU");
  registry.registerMetric<int>("HTTP requests RPS");

  MetricsFlusher flusher("metrics.txt", 15); // запись раз в секунду

  for (int32_t i = 0; i < 5; ++i) {
    registry.record("CPU", 0.5 + 0.1 * i);
    registry.record("HTTP requests RPS", 100 + i);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return 0;
}
