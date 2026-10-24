 
#include "BenchmarkRunner.hpp"
#include "CSVExporter.hpp"

#include <algorithm>
#include <array>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

constexpr int TRIALS = 7;

double median(std::vector<double> values) {
    std::sort(values.begin(), values.end());
    const std::size_t n = values.size();

    if (n % 2 == 1) {
        return values[n / 2];
    }

    return (values[n / 2 - 1] + values[n / 2]) / 2.0;
}

int main() {
    std::uint64_t iterations{};

    std::cout << "=== CPU Performance Toolkit ===\n";
    std::cout << "Iterations (1000 - 100000000): ";
    std::cin >> iterations;

    if (!std::cin || iterations < 1000 ||
        iterations > 100000000ULL) {
        std::cerr << "Invalid iterations.\n";
        return 1;
    }

    const std::array<unsigned int, 4> threadCounts = {1, 2, 4, 8};
    BenchmarkRunner runner;

    // Warm-up runs: their timings are not included in the results.
    std::cout << "\nWarming up benchmark...\n";
    auto warmupSequential = runner.runSequential(iterations);
    auto warmupParallel = runner.runParallel(iterations, 2);

    const std::uint64_t expectedChecksum =
        warmupSequential.getChecksum();

    if (warmupParallel.getChecksum() != expectedChecksum) {
        std::cerr << "Warm-up checksum mismatch!\n";
        return 1;
    }

    std::vector<double> sequentialTimes;
    std::vector<std::vector<double>> parallelTimes(threadCounts.size());
    std::vector<BenchmarkResult> results;

    // Alternate which mode runs first to reduce order bias.
    for (int trial = 0; trial < TRIALS; ++trial) {
        std::cout << "Trial " << trial + 1 << "/" << TRIALS << "\n";

        auto runSequential = [&]() {
            auto result = runner.runSequential(iterations);

            if (result.getChecksum() != expectedChecksum) {
                throw std::runtime_error("Sequential checksum mismatch");
            }

            sequentialTimes.push_back(result.getExecutionTimeMs());
        };

        auto runParallel = [&](std::size_t index,
                               unsigned int threads) {
            auto result = runner.runParallel(iterations, threads);

            if (result.getChecksum() != expectedChecksum) {
                throw std::runtime_error("Parallel checksum mismatch");
            }

            parallelTimes[index].push_back(result.getExecutionTimeMs());
        };

        if (trial % 2 == 0) {
            runSequential();
        }

        for (std::size_t i = 0; i < threadCounts.size(); ++i) {
            runParallel(i, threadCounts[i]);
        }

        if (trial % 2 == 1) {
            runSequential();
        }
    }

    const double sequentialAverage =
        std::accumulate(sequentialTimes.begin(),
                        sequentialTimes.end(), 0.0) /
        sequentialTimes.size();

    const double sequentialMedian = median(sequentialTimes);

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "\n--- Benchmark Results ---\n";
    std::cout << "Iterations: " << iterations << '\n';
    std::cout << "Trials per configuration: " << TRIALS << '\n';
    std::cout << "Sequential average: " << sequentialAverage << " ms\n";
    std::cout << "Sequential median:  " << sequentialMedian << " ms\n\n";

    std::cout << std::left
              << std::setw(10) << "Threads"
              << std::setw(16) << "Avg (ms)"
              << std::setw(16) << "Median (ms)"
              << std::setw(12) << "Speedup"
              << std::setw(14) << "Efficiency"
              << "Correctness\n";

    results.emplace_back("Sequential Average", iterations, 1,
                         sequentialAverage, expectedChecksum);
    results.emplace_back("Sequential Median", iterations, 1,
                         sequentialMedian, expectedChecksum);

    for (std::size_t i = 0; i < threadCounts.size(); ++i) {
        const double average =
            std::accumulate(parallelTimes[i].begin(),
                            parallelTimes[i].end(), 0.0) /
            parallelTimes[i].size();

        const double med = median(parallelTimes[i]);
        const double speedup = sequentialMedian / med;
        const double efficiency =
            speedup / threadCounts[i] * 100.0;

        std::cout << std::left
                  << std::setw(10) << threadCounts[i]
                  << std::setw(16) << average
                  << std::setw(16) << med
                  << std::setw(12) << speedup
                  << std::setw(14) << efficiency
                  << "PASSED\n";

        results.emplace_back("Parallel Average", iterations,
                             threadCounts[i], average, expectedChecksum);
        results.emplace_back("Parallel Median", iterations,
                             threadCounts[i], med, expectedChecksum);
    }

 

    CSVExporter exporter;
    if (!exporter.exportResults(results, "results/benchmark.csv")) {
        std::cerr << "Failed to export CSV.\n";
        return 1;
    }

    std::cout << "\nCSV saved: results/benchmark.csv\n";
    return 0;
}
