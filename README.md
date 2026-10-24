# CPU Performance Benchmark & Parallel Processing Toolkit

A C++17 benchmarking tool that compares sequential and multithreaded execution to study how thread count affects execution time, speedup, and parallel efficiency.

The project uses `std::thread` for parallel computation, validates results using checksums, and exports benchmark measurements to a CSV file for further analysis.

## Features

- **Sequential vs. Parallel Execution:** Compare single-threaded computation with multithreaded execution.
- **Multithreading:** Distribute computational work across 1, 2, 4, and 8 threads.
- **Workload Partitioning:** Divide iterations into chunks and assign them to worker threads.
- **Correctness Validation:** Compare checksums to verify that sequential and parallel computations produce matching results.
- **Repeated Benchmarking:** Perform warm-up runs and collect measurements across seven trials per configuration.
- **Performance Metrics:** Report average execution time, median execution time, speedup, and parallel efficiency.
- **CSV Export:** Save benchmark measurements to `results/benchmark.csv`.
- **Object-Oriented Design:** Organize benchmark execution, parallel processing, result storage, and CSV export into separate classes.

## Tech Stack

- C++17
- Standard Template Library (STL)
- `std::thread`
- `std::chrono`
- CMake
- CSV file handling

## Project Structure

```text
cpu-performance-toolkit/
├── include/
│   ├── BenchmarkResult.hpp
│   ├── BenchmarkRunner.hpp
│   ├── ParallelEngine.hpp
│   └── CSVExporter.hpp
├── src/
│   ├── BenchmarkRunner.cpp
│   ├── ParallelEngine.cpp
│   └── CSVExporter.cpp
├── results/
│   └── benchmark.csv
├── main.cpp
├── CMakeLists.txt
├── .gitignore
└── README.md
```

## Requirements

- A C++17-compatible compiler
- CMake
- A system with support for C++ threads

## Build and Run

### 1. Clone the repository

```bash
git clone https://github.com/mohdfarahidali987-sketch/CPU-performance-toolkit.git
cd CPU-performance-toolkit
```

### 2. Configure the project

```bash
cmake -S . -B build-release -DCMAKE_BUILD_TYPE=Release
```

### 3. Build

```bash
cmake --build build-release
```

### 4. Run

```bash
./build-release/cpu_benchmark
```

Enter an iteration count between `1000` and `100000000` when prompted.

The program benchmarks sequential execution and parallel execution using 1, 2, 4, and 8 threads.

## Benchmark Methodology

The current implementation:

1. Executes warm-up runs before collecting timed measurements.
2. Uses the sequential result as the reference checksum.
3. Runs seven timed trials for sequential execution and each parallel thread configuration.
4. Alternates the order of sequential and parallel measurements to reduce systematic timing bias.
5. Calculates average and median execution times.
6. Calculates speedup and parallel efficiency using median timings.
7. Verifies the checksum of every measured result.
8. Exports the collected summary results to CSV.

## Performance Metrics

**Speedup**

Speedup compares the sequential median time with the parallel median time.

`Speedup = Sequential Median / Parallel Median`

A speedup greater than `1` indicates that the parallel configuration was faster for that measurement.

**Parallel Efficiency**

`Efficiency (%) = (Speedup / Number of Threads) × 100`

Efficiency describes speedup relative to the number of threads. It can vary with workload size, thread-management overhead, CPU architecture, compiler optimizations, and system load.

## Sample Output

The following is an example from a local run with 10,000,000 iterations. Results are specific to that run and are not guaranteed on other systems.

| Threads | Median Time (ms) | Speedup | Efficiency |
|---:|---:|---:|---:|
| 1 | 3.984 | 0.937× | 93.7% |
| 2 | 1.997 | 1.870× | 93.5% |
| 4 | 1.184 | 3.155× | 78.9% |
| 8 | 0.950 | 3.931× | 49.1% |

All four configurations passed checksum validation in this run.

## CSV Results

Benchmark output is written to:

```text
results/benchmark.csv
```

The CSV includes the execution mode, iteration count, thread count, recorded time in milliseconds, and checksum.

You can open the file in Excel, Google Sheets, or another data-analysis tool to compare configurations.

## Limitations

- Benchmark results depend on the processor, operating system, compiler, build settings, and background system activity.
- Thread creation and scheduling add overhead, especially for small workloads.
- Sequential and parallel implementations may be optimized differently by the compiler. Therefore, measurements should be interpreted as observations of this implementation, not as universal hardware performance claims.
- Repeated trials improve measurement quality but do not eliminate all sources of variability.

## Future Improvements

- Add automated benchmarks across multiple iteration counts.
- Export raw trial measurements in addition to averages and medians.
- Add charts to visualize speedup and efficiency.
- Compare different workload sizes and scheduling strategies.
- Improve benchmark fairness by investigating compiler optimization and measurement effects.

## Learning Outcomes

This project explores:

- C++ object-oriented programming
- Multithreading and thread synchronization
- Workload partitioning
- Execution-time measurement with `std::chrono`
- Checksum-based correctness testing
- Performance analysis and CSV data export

## Author

**Muhammad Farahid Ali**

GitHub: [mohdfarahidali987-sketch](https://github.com/mohdfarahidali987-sketch)

---

*Built as a C++ systems-programming project to explore multithreading and performance benchmarking.*
