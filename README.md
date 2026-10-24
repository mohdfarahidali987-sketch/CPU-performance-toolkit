
# CPU Performance Benchmark & Parallel Processing Toolkit

A C++17 command-line application that compares sequential and
multithreaded execution of a computational workload.

## Features

- Sequential and parallel execution
- Configurable workload size and thread count
- Multithreading using `std::thread`
- Workload partitioning across threads
- Thread synchronization using `join()`
- Execution-time measurement
- Speedup and parallel-efficiency calculations
- Checksum-based correctness validation
- CSV export of benchmark results

## Tech Stack

- C++17
- C++ Standard Library
- Multithreading
- CMake

## Project Structure

```text
cpu-performance-toolkit/
├── main.cpp
├── CMakeLists.txt
├── include/
│   ├── BenchmarkResult.hpp
│   ├── BenchmarkRunner.hpp
│   ├── ParallelEngine.hpp
│   └── CSVExporter.hpp
├── src/
│   ├── BenchmarkRunner.cpp
│   ├── ParallelEngine.cpp
│   └── CSVExporter.cpp
└── results/
    └── benchmark.csv
```

## Build

Requirements: a C++17-compatible compiler and CMake 3.16+.

```bash
cmake -S . -B build-release -DCMAKE_BUILD_TYPE=Release
cmake --build build-release
```

## Run

```bash
./build-release/cpu_benchmark
```

Enter the number of iterations and threads when prompted.

## Metrics

- Execution time in milliseconds
- Speedup = sequential time / parallel time
- Parallel efficiency = speedup / thread count * 100

## Correctness

The application compares checksums from sequential and
parallel execution to verify that both produce the same result.

## Benchmark Notes

Results depend on compiler optimizations, CPU architecture,
workload size, thread overhead, and system load.

Run multiple trials before drawing performance conclusions.
Reported speedup is specific to this implementation and workload.

## Future Improvements

- Repeated trials and average/median measurements
- Automated unit tests
- More workload types
- Benchmark results visualization
- Hardware-aware thread-count selection
