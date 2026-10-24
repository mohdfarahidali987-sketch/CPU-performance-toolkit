
#ifndef BENCHMARK_RESULT_HPP
#define BENCHMARK_RESULT_HPP

#include <cstdint>
#include <string>

class BenchmarkResult {
private:
    std::string mode;
    std::uint64_t iterations;
    unsigned int threadCount;
    double executionTimeMs;
    std::uint64_t checksum;

public:
    BenchmarkResult(
        const std::string& mode,
        std::uint64_t iterations,
        unsigned int threadCount,
        double executionTimeMs,
        std::uint64_t checksum
    )
        : mode(mode),
          iterations(iterations),
          threadCount(threadCount),
          executionTimeMs(executionTimeMs),
          checksum(checksum) {}

    std::string getMode() const {
        return mode;
    }

    std::uint64_t getIterations() const {
        return iterations;
    }

    unsigned int getThreadCount() const {
        return threadCount;
    }

    double getExecutionTimeMs() const {
        return executionTimeMs;
    }

    std::uint64_t getChecksum() const {
        return checksum;
    }
};

#endif
