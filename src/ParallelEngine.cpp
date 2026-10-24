
#include "ParallelEngine.hpp"

#include <algorithm>
#include <stdexcept>
#include <thread>
#include <vector>

ParallelEngine::ParallelEngine(unsigned int threadCount)
    : threadCount(threadCount) {
    if (threadCount == 0) {
        throw std::invalid_argument("Thread count must be positive");
    }
}

std::uint64_t ParallelEngine::calculateWork(
    std::uint64_t start,
    std::uint64_t end
) const {
    constexpr std::uint64_t MOD = 1000000007ULL;
    std::uint64_t sum = 0;

    for (std::uint64_t i = start; i < end; ++i) {
        sum += (i * i + 31ULL * i + 7ULL) % MOD;
    }

    return sum;
}

std::uint64_t ParallelEngine::run(
    std::uint64_t iterations
) const {
    if (iterations == 0) {
        return 0;
    }

    unsigned int count = static_cast<unsigned int>(
        std::min<std::uint64_t>(threadCount, iterations)
    );

    std::vector<std::thread> workers;
    std::vector<std::uint64_t> partialSums(count, 0);

    std::uint64_t chunk = iterations / count;
    std::uint64_t remainder = iterations % count;
    std::uint64_t start = 1;

    for (unsigned int t = 0; t < count; ++t) {
        std::uint64_t length = chunk + (t < remainder ? 1 : 0);
        std::uint64_t end = start + length;

        workers.emplace_back([&, t, start, end]() {
            partialSums[t] = calculateWork(start, end);
        });

        start = end;
    }

    for (auto& worker : workers) {
        worker.join();
    }

    std::uint64_t total = 0;

    for (auto sum : partialSums) {
        total += sum;
    }

    return total;
}
