
#include "BenchmarkRunner.hpp"
#include "CSVExporter.hpp"

#include <filesystem>
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
    std::uint64_t iterations;
    unsigned int threads;

    std::cout << "=== CPU Performance Toolkit ===\n";
    std::cout << "Iterations (1000 - 100000000): ";
    std::cin >> iterations;

    if (!std::cin || iterations < 1000 ||
        iterations > 100000000ULL) {
        std::cerr << "Invalid iterations.\n";
        return 1;
    }

    std::cout << "Number of threads (1 - 64): ";
    std::cin >> threads;

    if (!std::cin || threads < 1 || threads > 64) {
        std::cerr << "Invalid thread count.\n";
        return 1;
    }

    BenchmarkRunner runner;

    auto sequential = runner.runSequential(iterations);
    auto parallel = runner.runParallel(iterations, threads);

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "\n--- Results ---\n";
    std::cout << "Sequential: "
              << sequential.getExecutionTimeMs() << " ms\n";
    std::cout << "Parallel:   "
              << parallel.getExecutionTimeMs() << " ms\n";

    if (sequential.getChecksum() != parallel.getChecksum()) {
        std::cerr << "ERROR: Checksums do not match!\n";
        return 1;
    }

    std::cout << "Correctness: PASSED\n";

    double sequentialTime = sequential.getExecutionTimeMs();
    double parallelTime = parallel.getExecutionTimeMs();

    if (parallelTime > 0.0) {
        double speedup = sequentialTime / parallelTime;
        double efficiency = speedup / threads * 100.0;

        std::cout << "Speedup: " << speedup << "x\n";
        std::cout << "Efficiency: " << efficiency << "%\n";
    }

 

    CSVExporter exporter;
    std::vector<BenchmarkResult> results{
        sequential, parallel
    };

    if (!exporter.exportResults(results, "results/benchmark.csv")) {
        std::cerr << "Failed to export CSV.\n";
        return 1;
    }

    std::cout << "CSV saved: results/benchmark.csv\n";
    return 0;
}
