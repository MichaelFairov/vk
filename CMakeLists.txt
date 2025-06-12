cmake_minimum_required(VERSION 3.14)
project(libmetrics)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(libmetrics_example
    main.cpp
    src/IMetric.hpp
    src/Metric.hpp
    src/MetricsRegistry.hpp
    src/MetricsFlusher.hpp
)

