
#include "BenchmarkRunner.hpp"
#include "ParallelEngine.hpp"

#include <chrono>
#include <stdexcept>

using Clock = std::chrono::steady_clock;

std::uint64_t BenchmarkRunner::calculateSequential(
    std::uint64_t iterations
) const {
    constexpr std::uint64_t MOD = 1000000007ULL;
    std::uint64_t sum = 0;

    for (std::uint64_t i = 1; i <= iterations; ++i) {
        sum += (i * i + 31ULL * i + 7ULL) % MOD;
    }

    return sum;
}

BenchmarkResult BenchmarkRunner::runSequential(
    std::uint64_t iterations
) const {
    auto start = Clock::now();
    auto checksum = calculateSequential(iterations);
    auto end = Clock::now();

    double elapsed = std::chrono::duration<double, std::milli>(
        end - start
    ).count();

    return BenchmarkResult(
        "Sequential", iterations, 1, elapsed, checksum
    );
}

BenchmarkResult BenchmarkRunner::runParallel(
    std::uint64_t iterations,
    unsigned int threadCount
) const {
    auto start = Clock::now();

    ParallelEngine engine(threadCount);
    auto checksum = engine.run(iterations);

    auto end = Clock::now();

    double elapsed = std::chrono::duration<double, std::milli>(
        end - start
    ).count();

    return BenchmarkResult(
        "Parallel", iterations, threadCount, elapsed, checksum
    );
}
