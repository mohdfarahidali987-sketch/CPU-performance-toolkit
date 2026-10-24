
#ifndef BENCHMARK_RUNNER_HPP
#define BENCHMARK_RUNNER_HPP

#include "BenchmarkResult.hpp"
#include <cstdint>

class BenchmarkRunner {
private:
    std::uint64_t calculateSequential(
        std::uint64_t iterations
    ) const;

public:
    BenchmarkResult runSequential(
        std::uint64_t iterations
    ) const;

    BenchmarkResult runParallel(
        std::uint64_t iterations,
        unsigned int threadCount
    ) const;
};

#endif
